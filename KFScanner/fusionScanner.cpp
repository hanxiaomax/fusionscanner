#include "fusionScanner.h"
#include <iostream>
#include <opencv2/viz/vizcore.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <kfusion\types.hpp>

/**************************************
 *  ��Ҫ����: ɨ�����࣬ʵ��ɨ���ǵ��߼�
 **************************************/ 

/*-------------------------------------* 
*	��������: ���캯��
*	������	  ��Ϊ����Դ�������		
--------------------------------------*/  
fusionScanner::fusionScanner(OpenNISource& source)
	:capture(source),
	time_ms(0),
	fusionstart(false)
{
	KinFuParams params = KinFuParams::default_params();//����Ĭ�ϲ���
	kinfu_sp = KinFu::Ptr( new KinFu(params) );//����Kinfu����
	kinfu_sp->PrintKFparms();
	capture.setRegistration(true);//���õ�����׼
	cv::viz::WCube cube(cv::Vec3d::all(0), cv::Vec3d(params.volume_size), true, cv::viz::Color::black());//����ϵ��
	viz.showWidget("cube", cube, params.volume_pose);//showWideget()�ᴴ��һ�����ڲ���
	viz.showWidget("coor", cv::viz::WCoordinateSystem(0.1));
}


/*-------------------------------------* 
*	��������: ���캯��
*	������	  ��Ϊ����Դ�������
*	������	  kinfu����
--------------------------------------*/  
fusionScanner::fusionScanner(OpenNISource& source,KinFuParams &params)
	:capture(source),
	 time_ms(0),
	 fusionstart(false)
{
	//KinFuParams p = params;//����ɾ����
	kinfu_sp = KinFu::Ptr( new KinFu(params) );//����Kinfu����
	kinfu_sp->PrintKFparms();
	capture.setRegistration(true);
}

/*-------------------------------------* 
*	��������: ��������
--------------------------------------*/ 
fusionScanner::~fusionScanner(void)
{

}

/*-------------------------------------* 
*	��������: ��ʼ�ں�
--------------------------------------*/ 
void fusionScanner::fusionStart()
{
	fusionstart=true;
}

/*-------------------------------------* 
*	��������: ֹͣ�ں�
--------------------------------------*/ 
void fusionScanner::fusionHold()
{
	fusionstart=false;
}
/*-------------------------------------* 
*	��������: �������
--------------------------------------*/ 
void fusionScanner::fusionReset()
{
	kinfu_sp->reset();
	clean_raycasted();
}

/*-------------------------------------* 
*	��������: ����ɨ������
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
			kinfu(depth_device_)   ;//kinfu�㷨�����ɹ�����true
		}
		creat_raycasted(kinfu);
	}
	else
	{
		capture.grab(depth, image);
	}
}

/*-------------------------------------* 
*	��������: ����������Ⱦ���ͼ������
--------------------------------------*/ 
void fusionScanner::creat_raycasted(KinFu& kinfu)
{		int mode=1;
        kinfu.renderImage(view_device_, mode);

        view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//�������󴢴�����
        view_device_.download(view_host_.ptr<void>(), view_host_.step);		
}

void fusionScanner::clean_raycasted()
{		
	view_host_.release();
}
/*-------------------------------------* 
*	��������: ��ȡ����
*	������	  �Ƿ�д�뵽�ļ�
--------------------------------------*/ 
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

			/*�ѵ�������д��pcd�ļ�*/
			{
				ScopeTime st("pcd writer");
				PCDFilewriter PCDw;
				PCDw.write("cloud_file.pcd",cloud,normal);
			}
		}
		//viz.showWidget("cloud", cv::viz::WPaintedCloud(cloud_host));//��ʾ����ɫ�ĵ���
		// 	viz.showWidget("normal",cv::viz::WCloudNormals(cloud_host,normal_host));//��ʾ���ߣ������Ƿ��Ѿ����㣿��

}

vertexes fusionScanner::getPointCloud(bool ToPly , bool ToPcd , bool with_normal)
{
	KinFu& kinfu=*kinfu_sp;
	kfusion::vertexes pcd;
	//����
	cuda::DeviceArray<Point> cloud = kinfu.tsdf().fetchCloud(cloud_buffer);//GPU�ڴ��е�һά����	
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//һά���󣬴���������(1�У�n��) CV_32FC4 32λ����4ͨ��
	//������
	cuda::DeviceArray<Point> normal;
	if(with_normal)
	{
		normal = kinfu.tsdf().fetchNormals(cloud,normal_buffer);//�������cloud����cloud_buffer�������޷���ȷdownload
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
	infobox.printInfo("���ڿ��ӻ��ĵ��������Ѿ�׼����:",InfoBox::SUC);
	if (ToPly||ToPly)
	{
			if(ToPly)/*�ѵ�������д��ply�ļ�*/
			{
				ScopeTime st("ply writer");
				PLYFilewriter PLYw;
				
				if(with_normal)
					PLYw .write("cloud_file-n.ply",cloud,normal);
				else
					PLYw .write("cloud_file.ply",cloud);
			}
			if(ToPcd)/*�ѵ�������д��pcd�ļ�*/
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