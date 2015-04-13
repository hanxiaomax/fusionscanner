#include "Fusion.h"
using namespace kfusion;

//���캯��
Fusion::Fusion(OpenNISource& source) : exit_ (false),  iteractive_mode_(false), capture_ (source)
{
	KinFuParams params = KinFuParams::default_params();//����Ĭ�ϲ���
	kinfu_ = KinFu::Ptr( new KinFu(params) );//����Kinfu����

	capture_.setRegistration(true);//���õ�����׼
	
}

Fusion::~Fusion(void)
{
}


void Fusion::show_raycasted(KinFu& kinfu)
{
		/*mode=1	��Ⱦ��ɫͼƬ
		mode=2		��Ⱦ��ɫͼƬ
		mode=3		˫ɫ
		*/
        const int mode =3;
		/*����ģʽ�£���ȾͼƬ����ȡ�۲�����̬�����򲻻�ȡ���������ص�renderImage����*/
        if (iteractive_mode_){
			//cout<<"iteractive_mode_"<<"-->render mode:";	
            kinfu.renderImage(view_device_, mode);//viz.getViewerPose()��Returns the current pose of the viewer.
		}
        else
		{	//cout<<"Not iteractive_mode_"<<"-->render mode:";
            kinfu.renderImage(view_device_, mode);
		}

        view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//�������󴢴�����
        view_device_.download(view_host_.ptr<void>(), view_host_.step);
		
		
}
