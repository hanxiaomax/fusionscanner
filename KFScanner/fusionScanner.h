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
	cv::Mat view_host_;//存放fusion显示
	cv::Mat depth, image;//存放深度数据和RGB数据
	cuda::DeviceArray<Point> cloud_buffer;//点云数据缓存
	cuda::DeviceArray<Normal> normal_buffer;//法线数据缓存
	

private:
	bool exit_, iteractive_mode_;
	bool fusionstart;
	OpenNISource& capture;
	KinFu::Ptr kinfu_sp;
	cuda::Image view_device_;
	cuda::Depth depth_device_;
	double time_ms;

public:
	void fusionStart();//启动融合
	void fusionHold();//暂停融合
	void fusionReset();//软件复位
	void update();//更新数据
	vertexes savePointCloud(bool ToPly , bool ToPcd , bool with_normal);//获取点云并保存到文件（或直接可视化）
	void getPointCloud(pcl::PointCloud<pcl::PointNormal> &input);
	
private:
	void creat_raycasted(KinFu& kinfu);//创建融合结果显示矩阵
	void clean_raycasted();
	
};

#endif