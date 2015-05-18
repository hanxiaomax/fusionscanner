#include "mainform.h"
#include <QtGui/QDialog>
#include "fusionScanner.h"


using namespace kfusion;
using namespace std;


mainform::mainform(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	//ui(Ui::mainformClass())//如果ui是对象的话这里其实没有必要，初始化已经完成

{
	/*指针初始化*/
	_scanner=NULL;
	_capture=NULL;

	ui.setupUi(this);
	/*设置mainTab*/
	ui.mainTab->setCurrentIndex(0);///要在setupUi之后
	connect(ui.defaultBtn,SIGNAL(clicked()),this,SLOT(resetToDefault()));
	connect(ui.showCloudBtn,SIGNAL(clicked()),this,SLOT(onShowCloudBtn()));//等价于on_ShowCloudBtn_clicked(),所以槽的命名不能是这个，否则会发射两次信号

}

mainform::~mainform()
{
	if (_capture)//如果不连接就直接关闭窗口，则_capture不存在
	{
		_capture->release();
	}
	
}

void mainform::resetToDefault()
{
	ui.delay_slider->setValue(5);
	ui.range_slider->setValue(1500);
	ui.full_rb->setChecked(true);
}


void mainform::on_connectKinect_triggered()
{

	int device = 0;
	cuda::setDevice (device);//设置GPU：0
	cuda::printShortCudaDeviceInfo (device);//打印GPU信息
	//检查GPU架构是否支持
	if(cuda::checkIfPreFermiGPU(device))
	{
		cout << endl << "Kinfu is not supported for pre-Fermi GPU architectures, and not built for them by default. Exiting..." << endl;
		return; 
	}

	cout<<"GPU check"<<endl;

	_capture = new OpenNISource();
	_capture->open(0);
	_scanner = new fusionScanner(*_capture);//创建scanner app实例，注意是一个指针
	
}
void mainform::on_ToolstartBtn_triggered()
{
	unsigned int delay=ui.delay_slider->value()*1000;//毫秒变为秒
	updateTimer=startTimer(33);//viewer定时器，33ms触发一次
	delayTimer=startTimer(delay);//fusionstart延时启动定时器，触发一次
}

//停止扫描:停止更新fusion数据
void mainform::on_ToolstopBtn_triggered()
{
	_scanner->fusionHold();
}

void mainform::on_TooldeleteBtn_triggered()
{

	_scanner->fusionReset();
	//ui.fusionViewer->updateScene();//只有在派生类中才可以通过派生类对象访问基类的protected成员。
	//showInViewer(_scanner->view_host_,ui.fusionViewer);
}

void mainform::onShowCloudBtn()
{
	_scanner->take_cloud();
}


void mainform::timerEvent(QTimerEvent *event)
{

	if (event->timerId()==updateTimer)
	{
		_scanner->update();//更新数据
		if(!_scanner->view_host_.empty())//view_host_在run()之前是空的，显示会出错
		{	
			showInViewer(_scanner->view_host_,ui.fusionViewer);
		}	
		showInViewer(_scanner->image,ui.RGBViewer);
		showInViewer(_scanner->depth,ui.depthViewer);
	}
	if (event->timerId()==delayTimer)
	{
		killTimer(delayTimer);//出发一次后关掉定时器
		_scanner->fusionStart();
	}

}
/*在glview中显示二维数据
params:
	cv::Mat& data
	glViewer *viewer
*/
void mainform::showInViewer(const cv::Mat& data,glViewer *viewer)
{
	if (data.channels()==1)//对深度数据进行变换
	{
		cv::Mat display;
		cv::normalize(data, display, 0, 255, cv::NORM_MINMAX, CV_8U);
		data.convertTo(display, CV_8U, 255.0/4000);
		viewer->showImage(display);
	}
	else{
		viewer->showImage(data);
	}
		
}



void mainform::on_actionSaveCloud_triggered()
{
	_scanner->take_cloud(true);
}

