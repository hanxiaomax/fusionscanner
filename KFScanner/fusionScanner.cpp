#include "fusionScanner.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
	fusion_start(false),
	camera_start(false)
{
	KinFuParams params = KinFuParams::default_params();//����Ĭ�ϲ���
	kinfu_sp = KinFu::Ptr( new KinFu(params) );//����Kinfu����
	kinfu_sp->PrintKFparms();
	capture.setRegistration(true);//���õ�����׼
}


/*-------------------------------------* 
*	��������: ���캯��
*	������	  ��Ϊ����Դ�������
*	������	  kinfu����
--------------------------------------*/  
fusionScanner::fusionScanner(OpenNISource& source,KinFuParams &params)
	:capture(source),
	 time_ms(0),
	 fusion_start(false)
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
	fusion_start=true;
}

/*-------------------------------------* 
*	��������: ֹͣ�ں�
--------------------------------------*/ 
void fusionScanner::fusionHold()
{
	fusion_start=false;
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
	if (fusion_start)
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
	else if(camera_start)
	{
		capture.grab(depth, image);
	}
}

/*-------------------------------------* 
*	��������: ����������Ⱦ���ͼ������
--------------------------------------*/ 
void fusionScanner::creat_raycasted(KinFu& kinfu)
{		int mode=1;
        kinfu.renderImage(rgb_device_, mode);

        view_host_.create(rgb_device_.rows(), rgb_device_.cols(), CV_8UC4);//�������󴢴�����
        rgb_device_.download(view_host_.ptr<void>(), view_host_.step);		
}

void fusionScanner::clean_raycasted()
{		
	view_host_.release();
}
/*-------------------------------------* 
*	��������: ��ȡ����
*	������	  �Ƿ�д�뵽�ļ�
--------------------------------------*/ 
pcl::PointCloud<pcl::PointNormal> fusionScanner::savePointCloud(bool ToPly , bool ToPcd)
{
	KinFu& kinfu=*kinfu_sp;
	pcl::PointCloud<pcl::PointNormal> pcd;
	//����
	cuda::DeviceArray<Point> cloud = kinfu.tsdf().fetchCloud(cloud_buffer);//GPU�ڴ��е�һά����	
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//һά���󣬴���������(1�У�n��) CV_32FC4 32λ����4ͨ��
	//������
	cuda::DeviceArray<Point> normal;
	
	normal = kinfu.tsdf().fetchNormals(cloud,normal_buffer);//�������cloud����cloud_buffer�������޷���ȷdownload
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
	infobox.printInfo("���ڿ��ӻ��ĵ��������Ѿ�׼����:",InfoBox::SUC);
	if (ToPly||ToPcd)
	{
			if(ToPly)/*�ѵ�������д��ply�ļ�*/
			{
				ScopeTime st("ply writer");
				PLYFilewriter PLYw;
				PLYw .write("cloud_file-n.ply",cloud,normal);
				infobox.printInfo("PLY����:",InfoBox::SUC);
				
			}
			if(ToPcd)/*�ѵ�������д��pcd�ļ�*/
			{
				ScopeTime st("pcd writer");
				PCDFilewriter PCDw;
				PCDw.write("000cloud_file.pcd",cloud,normal);
				infobox.printInfo("PCD����:",InfoBox::SUC);
			}
	}
	return pcd ;
}

void fusionScanner::getPointCloud(pcl::PointCloud<pcl::PointNormal> &input)
{
	KinFu& kinfu=*kinfu_sp;
	//����
	cuda::DeviceArray<Point> cloud = kinfu.tsdf().fetchCloud(cloud_buffer);//GPU�ڴ��е�һά����	
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//һά���󣬴���������(1�У�n��) CV_32FC4 32λ����4ͨ��
	for (int i = 0; i < cloud_host.cols; ++i) 
	{
		pcl::PointNormal point;

		point.x=cloud_host.at<cv::Vec4f>(0,i)[0];
		point.y=cloud_host.at<cv::Vec4f>(0,i)[1];
		point.z=cloud_host.at<cv::Vec4f>(0,i)[2];
		
		(input).push_back(point);
	}
	

}