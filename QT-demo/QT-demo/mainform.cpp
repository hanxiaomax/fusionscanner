#include "mainform.h"
#include "ui_mainform.h"
#include <io/capture.hpp>
#include <iostream>
#include <qDebug>
#include "Fusion.h"
using namespace kfusion;
using namespace std;
mainForm::mainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui=new Ui::mainFormClass;
	ui->setupUi(this);
}

mainForm::~mainForm()
{
}

//TODO:Ҳ�����ѡ��򿪲�ͬ�����û���oni�ļ�
void mainForm::on_ConnectKinect_triggered(){
	

	_capture.open(0);
	Fusion fusion (_capture);
	

}
void mainForm::on_Scan_triggered(){

	int id=0;
	
	id=startTimer(0);
}

//ѭ������ÿһ֡����
void mainForm::timerEvent(QTimerEvent *event)
{
	event->timerId();//�õ��������¼���timerId
	
		// Do what you want with the image :-)
	
		// Show the image
		
		//show_raycasted(kinfu);
		
		//ui->Dviewer->showImage( depth );
		//ui->GRBviewer->showImage(image);
	
}

// void mainForm::show_raycasted(KinFu& kinfu){
// 	const int mode =3;
// 	kinfu.renderImage(view_device_,mode);
// 	view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//�������󴢴�����
// 	view_device_.download(view_host_.ptr<void>(), view_host_.step);
// 	ui->Fusionviewer->showImage(view_host_);
// }
