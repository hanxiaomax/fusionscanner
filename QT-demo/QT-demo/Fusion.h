#pragma once
#ifndef FUSION_H_H
#define FUSION_H_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <kfusion/kinfu.hpp>
#include <io/capture.hpp>

using namespace kfusion;
class Fusion
{
public:

	Fusion(OpenNISource& source);

	~Fusion(void);
private:
	bool exit_, iteractive_mode_;
	OpenNISource& capture_;
	KinFu::Ptr kinfu_;//指针不需要初始化

	cv::Mat view_host_;
	cuda::Image view_device_;
	cuda::Depth depth_device_;
	cuda::DeviceArray<Point> cloud_buffer;


public:
	cv::Mat get_depth(const cv::Mat& depth);
	cv::Mat get_image(const cv::Mat& image);
	void show_raycasted(KinFu& kinfu);
	
};

#endif //FUSION_H_H