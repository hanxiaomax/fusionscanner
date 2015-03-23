#ifndef ANIMAL_H_H
#define ANIMAL_H_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/viz/vizcore.hpp>
#include <kfusion/kinfu.hpp>
#include <io/capture.hpp>
#include <iostream>

using namespace kfusion;

class QTApp
{
	//¼üÅÌ°´¼ü´¦Àí
    static void KeyboardCallback(const cv::viz::KeyboardEvent& event, void* pthis);
    QTApp(OpenNISource& source);

    void show_depth(const cv::Mat& depth);
    void show_raycasted(KinFu& kinfu);
    void take_cloud(KinFu& kinfu);
    
    bool execute();
    
    bool exit_, iteractive_mode_;
    OpenNISource& capture_;
    KinFu::Ptr kinfu_;
    cv::viz::Viz3d viz;

    cv::Mat view_host_;
    cuda::Image view_device_;
    cuda::Depth depth_device_;
    cuda::DeviceArray<Point> cloud_buffer;
};



#endif ANIMAL_H_H 