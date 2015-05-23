#include "fusionScanner.h"
#include <iostream>
#include <opencv2/viz/vizcore.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

fusionScanner::fusionScanner(OpenNISource& source)
	:capture(source),
	time_ms(0),
	fusionstart(false)
{
	KinFuParams params = KinFuParams::default_params();//设置默认参数
	kinfu_sp = KinFu::Ptr( new KinFu(params) );//创建Kinfu对象
	kinfu_sp->PrintKFparms();
	capture.setRegistration(true);//设置点云配准
	cv::viz::WCube cube(cv::Vec3d::all(0), cv::Vec3d(params.volume_size), true, cv::viz::Color::apricot());//坐标系？
	viz.showWidget("cube", cube, params.volume_pose);//showWideget()会创建一个窗口部件
	viz.showWidget("coor", cv::viz::WCoordinateSystem(0.1));

}


//带自定义参数的构造函数
fusionScanner::fusionScanner(OpenNISource& source,KinFuParams &params)
	:capture(source),
	 time_ms(0),
	 fusionstart(false)
{
	KinFuParams p = params;
	kinfu_sp = KinFu::Ptr( new KinFu(p) );//创建Kinfu对象
	kinfu_sp->PrintKFparms();
	capture.setRegistration(true);//设置点云配准
	cv::viz::WCube cube(cv::Vec3d::all(0), cv::Vec3d(params.volume_size), true, cv::viz::Color::apricot());//坐标系？
        viz.showWidget("cube", cube, params.volume_pose);//showWideget()会创建一个窗口部件
        viz.showWidget("coor", cv::viz::WCoordinateSystem(0.1));

}


fusionScanner::~fusionScanner(void)
{

}


void fusionScanner::fusionStart()
{
	fusionstart=true;
}

void fusionScanner::fusionHold()
{
	fusionstart=false;
}
void fusionScanner::fusionReset()
{
	kinfu_sp->reset();
	clean_raycasted();
}

//获取更新数据
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
		show_raycasted(kinfu);
		//viz.setViewerPose(kinfu_sp->getCameraPose());
		viz.spinOnce(3, true);
	}
	else
	{
		capture.grab(depth, image);
	}

}


void fusionScanner::show_raycasted(KinFu& kinfu)
{		int mode=1;
        kinfu.renderImage(view_device_, mode);

        view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//创建矩阵储存像素
        view_device_.download(view_host_.ptr<void>(), view_host_.step);		
}

void fusionScanner::clean_raycasted()
{		
	view_host_.release();
}

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

			// 			/*把点云数据写入pcd文件*/
			{
				ScopeTime st("pcd writer");
				PCDFilewriter PCDw;
				PCDw.write("cloud_file.pcd",cloud,normal);
			}
		}

		// 
		// 
		// 	/*显示点云或有颜色的点云*/
		// 
		// 	//viz.showWidget("cloud", cv::viz::WCloud(cloud_host));//显示点云
		viz.showWidget("cloud", cv::viz::WPaintedCloud(cloud_host));//显示有颜色的点云
		// 	viz.showWidget("normal",cv::viz::WCloudNormals(cloud_host,normal_host));//显示法线（法线是否已经计算？）
	

}