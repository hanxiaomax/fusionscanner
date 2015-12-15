#pragma once
#ifndef FUSION_SCANNER_H_H
#define FUSION_SCANNER_H_H

#include <io/capture.hpp>
#include <kfusion/CloudIO.h>

using namespace kfusion;

class fusionScanner
{
public:
	fusionScanner(void);
	fusionScanner(OpenNISource &source);
	fusionScanner(OpenNISource &source,KinFuParams &params);
	~fusionScanner(void);
public:
	cv::Mat view_host_;//���fusion��ʾ
	cv::Mat depth, image;//���������ݺ�RGB����
	cuda::DeviceArray<Point> cloud_buffer;//�������ݻ���
	cuda::DeviceArray<Normal> normal_buffer;//�������ݻ���
	

private:
	OpenNISource& capture;//openNI�豸
	KinFu::Ptr kinfu_sp;//kinfuָ��
	cuda::Image rgb_device_;//��Ƶ��������
	cuda::Depth depth_device_;//�����������
	double time_ms;
	bool fusion_start,camera_start;//�Ƿ�������ͷ���Ƿ�����ں�

public:
	void fusionStart();//�����ں�
	void fusionHold();//��ͣ�ں�
	void fusionReset();//�����λ
	void cameraStart(){camera_start=true;};
	void cameraHold(){camera_start=false;};
	
	void update();//��������
	pcl::PointCloud<pcl::PointNormal> fusionScanner::savePointCloud(bool ToPly , bool ToPcd);//��ȡ���Ʋ����浽�ļ�����ֱ�ӿ��ӻ���
	void getPointCloud(pcl::PointCloud<pcl::PointNormal> &input);
	
private:
	void creat_raycasted(KinFu& kinfu);//�����ںϽ����ʾ����
	void clean_raycasted();
	
};

#endif