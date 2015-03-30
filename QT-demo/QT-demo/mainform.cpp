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

//TODO:也许可以选择打开不同的配置或者oni文件
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
		/*mode=1	渲染无色图片
		mode=2		渲染彩色图片
		mode=3		双色
		*/
        const int mode =3;
		/*交互模式下，渲染图片，获取观察者姿态，否则不获取，调用重载的renderImage函数*/
       
        kinfu.renderImage(view_device_, mode);
		

        view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//创建矩阵储存像素
        view_device_.download(view_host_.ptr<void>(), view_host_.step);

		ui->Fusionviewer->showImage(view_host_);
        
    }