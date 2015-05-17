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

	capture.setRegistration(true);//���õ�����׼
	cv::viz::WCube cube(cv::Vec3d::all(0), cv::Vec3d(params.volume_size), true, cv::viz::Color::apricot());//����ϵ��
        viz.showWidget("cube", cube, params.volume_pose);//showWideget()�ᴴ��һ�����ڲ���
        viz.showWidget("coor", cv::viz::WCoordinateSystem(0.1));

}


fusionScanner::~fusionScanner(void)
{
	capture.release();
}


void fusionScanner::run()
{
	fusionstart=true;
}

void fusionScanner::hold()
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

	capture.grab(depth, image);
	if (fusionstart)
	{
		KinFu& kinfu=*kinfu_sp;
		
		depth_device_.upload(depth.data, depth.step, depth.rows, depth.cols);
		{
			SampledScopeTime fps(time_ms); 
			(void)fps;
			kinfu(depth_device_)   ;//kinfu�㷨�����ɹ�����true
		}
		show_raycasted(kinfu);
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
	view_device_.release();
}
