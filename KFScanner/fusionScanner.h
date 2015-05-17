#pragma once
#ifndef FUSION_SCANNER_H_H
#define FUSION_SCANNER_H_H
#include <kfusion/kinfu.hpp>
#include <io/capture.hpp>
using namespace kfusion;


class fusionScanner
{
public:
	fusionScanner(void);
	fusionScanner(OpenNISource &source);
	~fusionScanner(void);
public:
	cv::Mat view_host_;
	cv::Mat depth, image;


private:
	bool exit_, iteractive_mode_;
	bool fusionstart;
	OpenNISource& capture;
	KinFu::Ptr kinfu_sp;
	cuda::Image view_device_;
	cuda::Depth depth_device_;
	cuda::DeviceArray<Point> cloud_buffer;//µãÔÆÊý¾Ý»º´æ

	cuda::DeviceArray<Normal> normal_buffer;
	double time_ms;

	cv::viz::Viz3d viz;
public:
	void run();
	void update();
	void hold();
	void fusionReset();
private:
	void show_raycasted(KinFu& kinfu);
	void clean_raycasted();

};

#endif