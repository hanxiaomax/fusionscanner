#include "fusionScanner.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
	fusion_start(false),
	camera_start(false)
{
	KinFuParams params = KinFuParams::default_params();//设置默认参数
	kinfu_sp = KinFu::Ptr( new KinFu(params) );//创建Kinfu对象
	kinfu_sp->PrintKFparms();
	capture.setRegistration(true);//设置点云配准
}


/*-------------------------------------* 
*	功能描述: 构造函数
*	参数：	  作为输入源的摄像机
*	参数：	  kinfu参数
--------------------------------------*/  
fusionScanner::fusionScanner(OpenNISource& source,KinFuParams &params)
	:capture(source),
	 time_ms(0),
	 fusion_start(false)
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
	fusion_start=true;
}

/*-------------------------------------* 
*	功能描述: 停止融合
--------------------------------------*/ 
void fusionScanner::fusionHold()
{
	fusion_start=false;
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
	if (fusion_start)
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
	else if(camera_start)
	{
		capture.grab(depth, image);
	}
}

/*-------------------------------------* 
*	功能描述: 创建光照渲染后的图像数据
--------------------------------------*/ 
void fusionScanner::creat_raycasted(KinFu& kinfu)
{		int mode=1;
        kinfu.renderImage(rgb_device_, mode);

        view_host_.create(rgb_device_.rows(), rgb_device_.cols(), CV_8UC4);//创建矩阵储存像素
        rgb_device_.download(view_host_.ptr<void>(), view_host_.step);		
}

void fusionScanner::clean_raycasted()
{		
	view_host_.release();
}
/*-------------------------------------* 
*	功能描述: 获取点云
*	参数：	  是否写入到文件
--------------------------------------*/ 
pcl::PointCloud<pcl::PointNormal> fusionScanner::savePointCloud(bool ToPly , bool ToPcd)
{
	KinFu& kinfu=*kinfu_sp;
	pcl::PointCloud<pcl::PointNormal> pcd;
	//点云
	cuda::DeviceArray<Point> cloud = kinfu.tsdf().fetchCloud(cloud_buffer);//GPU内存中的一维矩阵	
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//一维矩阵，存放无序点云(1行，n列) CV_32FC4 32位浮点4通道
	//法向量
	cuda::DeviceArray<Point> normal;
	
	normal = kinfu.tsdf().fetchNormals(cloud,normal_buffer);//传入的是cloud不是cloud_buffer，后者无法正确download
	cv::Mat normal_host(1, (int)cloud.size(), CV_32FC4);
	normal.download(normal_host.ptr<Normal>());

	
	
	cloud.download(cloud_host.ptr<Point>());
	for (int i = 0; i < cloud_host.cols; ++i) 
	{
		pcl::PointNormal p;
		p.x=cloud_host.at<cv::Vec4f>(0,i)[0];
		p.y=cloud_host.at<cv::Vec4f>(0,i)[1];
		p.z=cloud_host.at<cv::Vec4f>(0,i)[2];
		p.normal_x=normal_host.at<cv::Vec4f>(0,i)[0];
		p.normal_y=normal_host.at<cv::Vec4f>(0,i)[1];
		p.normal_z=normal_host.at<cv::Vec4f>(0,i)[2];
		pcd.points.push_back(p);
	}
	InfoBox infobox("getPointCloud");
	infobox.printInfo("用于可视化的点云数据已经准备好:",InfoBox::SUC);
	if (ToPly||ToPcd)
	{
			if(ToPly)/*把点云数据写入ply文件*/
			{
				ScopeTime st("ply writer");
				PLYFilewriter PLYw;
				PLYw .write("cloud_file-n.ply",cloud,normal);
				infobox.printInfo("PLY生成:",InfoBox::SUC);
				
			}
			if(ToPcd)/*把点云数据写入pcd文件*/
			{
				ScopeTime st("pcd writer");
				PCDFilewriter PCDw;
				PCDw.write("000cloud_file.pcd",cloud,normal);
				infobox.printInfo("PCD生成:",InfoBox::SUC);
			}
	}
	return pcd ;
}

void fusionScanner::getPointCloud(pcl::PointCloud<pcl::PointNormal> &input)
{
	KinFu& kinfu=*kinfu_sp;
	//点云
	cuda::DeviceArray<Point> cloud = kinfu.tsdf().fetchCloud(cloud_buffer);//GPU内存中的一维矩阵	
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//一维矩阵，存放无序点云(1行，n列) CV_32FC4 32位浮点4通道
	for (int i = 0; i < cloud_host.cols; ++i) 
	{
		pcl::PointNormal point;

		point.x=cloud_host.at<cv::Vec4f>(0,i)[0];
		point.y=cloud_host.at<cv::Vec4f>(0,i)[1];
		point.z=cloud_host.at<cv::Vec4f>(0,i)[2];
		
		(input).push_back(point);
	}
	

}