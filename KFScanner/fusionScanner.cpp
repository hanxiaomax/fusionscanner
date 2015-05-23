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
	KinFuParams params = KinFuParams::default_params();//����Ĭ�ϲ���
	kinfu_sp = KinFu::Ptr( new KinFu(params) );//����Kinfu����
	kinfu_sp->PrintKFparms();
	capture.setRegistration(true);//���õ�����׼
	cv::viz::WCube cube(cv::Vec3d::all(0), cv::Vec3d(params.volume_size), true, cv::viz::Color::apricot());//����ϵ��
	viz.showWidget("cube", cube, params.volume_pose);//showWideget()�ᴴ��һ�����ڲ���
	viz.showWidget("coor", cv::viz::WCoordinateSystem(0.1));

}


//���Զ�������Ĺ��캯��
fusionScanner::fusionScanner(OpenNISource& source,KinFuParams &params)
	:capture(source),
	 time_ms(0),
	 fusionstart(false)
{
	KinFuParams p = params;
	kinfu_sp = KinFu::Ptr( new KinFu(p) );//����Kinfu����
	kinfu_sp->PrintKFparms();
	capture.setRegistration(true);//���õ�����׼
	cv::viz::WCube cube(cv::Vec3d::all(0), cv::Vec3d(params.volume_size), true, cv::viz::Color::apricot());//����ϵ��
        viz.showWidget("cube", cube, params.volume_pose);//showWideget()�ᴴ��һ�����ڲ���
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

//��ȡ��������
void fusionScanner::update(){
	if (fusionstart)
	{
		capture.grab(depth, image);
		KinFu& kinfu=*kinfu_sp;
		
		depth_device_.upload(depth.data, depth.step, depth.rows, depth.cols);
		{
			SampledScopeTime fps(time_ms); 
			(void)fps;
			kinfu(depth_device_)   ;//kinfu�㷨�����ɹ�����true
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

        view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//�������󴢴�����
        view_device_.download(view_host_.ptr<void>(), view_host_.step);		
}

void fusionScanner::clean_raycasted()
{		
	view_host_.release();
}

void fusionScanner::take_cloud(bool writetofile)
{
	/*��ȡ�������*/ 
	
		KinFu& kinfu=*kinfu_sp;
		cuda::DeviceArray<Point> cloud = kinfu.tsdf().fetchCloud(cloud_buffer);//GPU�ڴ��е�һά����
		cuda::DeviceArray<Point> normal = kinfu.tsdf().fetchNormals(cloud,normal_buffer);//�������cloud����cloud_buffer�������޷���ȷdownload

		


		cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//һά���󣬴���������(1�У�n��) CV_32FC4 32λ����4ͨ��
		cv::Mat normal_host(1, (int)cloud.size(), CV_32FC4);


		cloud.download(cloud_host.ptr<Point>());
		normal.download(normal_host.ptr<Normal>());

		InfoBox infobox("take_cloud");
		infobox.printInfo("���ƻ�ȡ:",InfoBox::SUC);



		if (writetofile)
		{
			/*�ѵ�������д��ply�ļ�*/
			{
				ScopeTime st("ply writer");
				PLYFilewriter PLYw;
				PLYw .write("cloud_file.ply",cloud);
				PLYw .write("cloud_file-n.ply",cloud,normal);
			}

			// 			/*�ѵ�������д��pcd�ļ�*/
			{
				ScopeTime st("pcd writer");
				PCDFilewriter PCDw;
				PCDw.write("cloud_file.pcd",cloud,normal);
			}
		}

		// 
		// 
		// 	/*��ʾ���ƻ�����ɫ�ĵ���*/
		// 
		// 	//viz.showWidget("cloud", cv::viz::WCloud(cloud_host));//��ʾ����
		viz.showWidget("cloud", cv::viz::WPaintedCloud(cloud_host));//��ʾ����ɫ�ĵ���
		// 	viz.showWidget("normal",cv::viz::WCloudNormals(cloud_host,normal_host));//��ʾ���ߣ������Ƿ��Ѿ����㣿��
	

}