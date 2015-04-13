#include "Fusion.h"
using namespace kfusion;

//构造函数
Fusion::Fusion(OpenNISource& source) : exit_ (false),  iteractive_mode_(false), capture_ (source)
{
	KinFuParams params = KinFuParams::default_params();//设置默认参数
	kinfu_ = KinFu::Ptr( new KinFu(params) );//创建Kinfu对象

	capture_.setRegistration(true);//设置点云配准
	
}

Fusion::~Fusion(void)
{
}


void Fusion::show_raycasted(KinFu& kinfu)
{
		/*mode=1	渲染无色图片
		mode=2		渲染彩色图片
		mode=3		双色
		*/
        const int mode =3;
		/*交互模式下，渲染图片，获取观察者姿态，否则不获取，调用重载的renderImage函数*/
        if (iteractive_mode_){
			//cout<<"iteractive_mode_"<<"-->render mode:";	
            kinfu.renderImage(view_device_, mode);//viz.getViewerPose()：Returns the current pose of the viewer.
		}
        else
		{	//cout<<"Not iteractive_mode_"<<"-->render mode:";
            kinfu.renderImage(view_device_, mode);
		}

        view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//创建矩阵储存像素
        view_device_.download(view_host_.ptr<void>(), view_host_.step);
		
		
}
