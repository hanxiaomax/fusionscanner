#include "mainform.h"
#include "ui_mainform.h"
#include <io/capture.hpp>
#include <iostream>
#include <qDebug>
using namespace kfusion;

mainForm::mainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),ui(new Ui::mainFormClass)
{
	ui->setupUi(this);
}

mainForm::~mainForm()
{
}

//TODO:Ҳ�����ѡ��򿪲�ͬ�����û���oni�ļ�
void mainForm::on_actionKinect_triggered()
{
	_capture.open(0);
	
	startTimer(0);
	
}


void mainForm::timerEvent(QTimerEvent *event)
{
	cv::Mat depth, image;
	

	// Do what you want with the image :-)

	// Show the image
	_capture.grab(depth, image);
	
	ui->Dviewer->showImage( depth );
	ui->GRBviewer->showImage(image);
	
}

void mainForm::show_raycasted(KinFu& kinfu)
    {
		/*mode=1	��Ⱦ��ɫͼƬ
		mode=2		��Ⱦ��ɫͼƬ
		mode=3		˫ɫ
		*/
        const int mode =3;
		/*����ģʽ�£���ȾͼƬ����ȡ�۲�����̬�����򲻻�ȡ���������ص�renderImage����*/
       
        kinfu.renderImage(view_device_, mode);
		

        view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//�������󴢴�����
        view_device_.download(view_host_.ptr<void>(), view_host_.step);

		ui->Fusionviewer->showImage(view_host_);
        
    }