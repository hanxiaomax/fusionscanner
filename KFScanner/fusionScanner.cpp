#include "fusionScanner.h"
#include <iostream>
#include <opencv2/viz/vizcore.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <kfusion\types.hpp>

/**************************************
 *  简要描述: 扫描仪类，实现扫描仪的逻辑
 **************************************/ 

/*-------------------------------------* 
*	功能描述: 构造函数
*	参数：	  作为输入源的摄像机		
--------------------------------------*/  
fusionScanner::fusionScanner(OpenNISource& source)
	:capture(source),
	time_ms(0),
	fusionstart(false)
{
	KinFuParams params = KinFuParams::default_params();//设置默认参数
	kinfu_sp = KinFu::Ptr( new KinFu(params) );//创建Kinfu对象
	kinfu_sp->PrintKFparms();
	capture.setRegistration(true);//设置点云配准
	cv::viz::WCube cube(cv::Vec3d::all(0), cv::Vec3d(params.volume_size), true, cv::viz::Color::black());//坐标系？
	viz.showWidget("cube", cube, params.volume_pose);//showWideget()会创建一个窗口部件
	viz.showWidget("coor", cv::viz::WCoordinateSystem(0.1));
}


/*-------------------------------------* 
*	功能描述: 构造函数
*	参数：	  作为输入源的摄像机
*	参数：	  kinfu参数
--------------------------------------*/  
fusionScanner::fusionScanner(OpenNISource& source,KinFuParams &params)
	:capture(source),
	 time_ms(0),
	 fusionstart(false)
{
	//KinFuParams p = params;//可以删掉？
	kinfu_sp = KinFu::Ptr( new KinFu(params) );//创建Kinfu对象
	kinfu_sp->PrintKFparms();
	capture.setRegistration(true);
}

/*-------------------------------------* 
*	功能描述: 析构函数
--------------------------------------*/ 
fusionScanner::~fusionScanner(void)
{

}

/*-------------------------------------* 
*	功能描述: 开始融合
--------------------------------------*/ 
void fusionScanner::fusionStart()
{
	fusionstart=true;
}

/*-------------------------------------* 
*	功能描述: 停止融合
--------------------------------------*/ 
void fusionScanner::fusionHold()
{
	fusionstart=false;
}
/*-------------------------------------* 
*	功能描述: 重置相机
--------------------------------------*/ 
void fusionScanner::fusionReset()
{
	kinfu_sp->reset();
	clean_raycasted();
}

/*-------------------------------------* 
*	功能描述: 更新扫描数据
--------------------------------------*/ 
void fusionScanner::update(){
	if (fusionstart)
	{
		capture.grab(depth, image);
		KinFu& kinfu=*kinfu_sp;
		
		depth_device_.upload(depth.data, depth.step, depth.rows, depth.cols);
		{
			SampledScopeTime fps(time_ms); 
			(void)fps;
			kinfu(depth_device_)   ;//kinfu算法处理，成功返回true
		}
		creat_raycasted(kinfu);
	}
	else
	{
		capture.grab(depth, image);
	}
}

/*-------------------------------------* 
*	功能描述: 创建光照渲染后的图像数据
--------------------------------------*/ 
void fusionScanner::creat_raycasted(KinFu& kinfu)
{		int mode=1;
        kinfu.renderImage(view_device_, mode);

        view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//创建矩阵储存像素
        view_device_.download(view_host_.ptr<void>(), view_host_.step);		
}

void fusionScanner::clean_raycasted()
{		
	view_host_.release();
}
/*-------------------------------------* 
*	功能描述: 获取点云
*	参数：	  是否写入到文件
--------------------------------------*/ 
void fusionScanner::take_cloud(bool writetofile)
{
	/*获取点云相关*/ 
	
		KinFu& kinfu=*kinfu_sp;
		cuda::DeviceArray<Point> cloud = kinfu.tsdf().fetchCloud(cloud_buffer);//GPU内存中的一维矩阵
		cuda::DeviceArray<Point> normal = kinfu.tsdf().fetchNormals(cloud,normal_buffer);//传入的是cloud不是cloud_buffer，后者无法正确download
		cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//一维矩阵，存放无序点云(1行，n列) CV_32FC4 32位浮点4通道
		cv::Mat normal_host(1, (int)cloud.size(), CV_32FC4);

		cloud.download(cloud_host.ptr<Point>());
		normal.download(normal_host.ptr<Normal>());

		InfoBox infobox("take_cloud");
		infobox.printInfo("点云获取:",InfoBox::SUC);
		if (writetofile)
		{
			/*把点云数据写入ply文件*/
			{
				ScopeTime st("ply writer");
				PLYFilewriter PLYw;
				PLYw .write("cloud_file.ply",cloud);
				PLYw .write("cloud_file-n.ply",cloud,normal);
			}

			/*把点云数据写入pcd文件*/
			{
				ScopeTime st("pcd writer");
				PCDFilewriter PCDw;
				PCDw.write("cloud_file.pcd",cloud,normal);
			}
		}
		//viz.showWidget("cloud", cv::viz::WPaintedCloud(cloud_host));//显示有颜色的点云
		// 	viz.showWidget("normal",cv::viz::WCloudNormals(cloud_host,normal_host));//显示法线（法线是否已经计算？）

}

vertexes fusionScanner::getPointCloud(bool ToPly , bool ToPcd , bool with_normal)
{
	KinFu& kinfu=*kinfu_sp;
	kfusion::vertexes pcd;
	//点云
	cuda::DeviceArray<Point> cloud = kinfu.tsdf().fetchCloud(cloud_buffer);//GPU内存中的一维矩阵	
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//一维矩阵，存放无序点云(1行，n列) CV_32FC4 32位浮点4通道
	//法向量
	cuda::DeviceArray<Point> normal;
	if(with_normal)
	{
		normal = kinfu.tsdf().fetchNormals(cloud,normal_buffer);//传入的是cloud不是cloud_buffer，后者无法正确download
		cv::Mat normal_host(1, (int)cloud.size(), CV_32FC4);
		normal.download(normal_host.ptr<Normal>());

	}
	
	cloud.download(cloud_host.ptr<Point>());
	for (int i = 0; i < cloud_host.cols; ++i) 
	{
		cv::Point3d vertex;
		vertex.x=cloud_host.at<cv::Vec4f>(0,i)[0];
		vertex.y=cloud_host.at<cv::Vec4f>(0,i)[1];
		vertex.z=cloud_host.at<cv::Vec4f>(0,i)[2];
		
		pcd.push_back(vertex);
	}
	InfoBox infobox("getPointCloud");
	infobox.printInfo("用于可视化的点云数据已经准备好:",InfoBox::SUC);
	if (ToPly||ToPly)
	{
			if(ToPly)/*把点云数据写入ply文件*/
			{
				ScopeTime st("ply writer");
				PLYFilewriter PLYw;
				
				if(with_normal)
					PLYw .write("cloud_file-n.ply",cloud,normal);
				else
					PLYw .write("cloud_file.ply",cloud);
			}
			if(ToPcd)/*把点云数据写入pcd文件*/
			{
				ScopeTime st("pcd writer");
				PCDFilewriter PCDw;
				if(with_normal)
					PCDw.write("cloud_file.pcd",cloud,normal);
				else
					PCDw.write("cloud_file.pcd",cloud);
			}
	}
	
	return pcd;
}