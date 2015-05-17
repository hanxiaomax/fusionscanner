#include "mainform.h"
#include <QtGui/QDialog>
#include "fusionScanner.h"


using namespace kfusion;
using namespace std;


mainform::mainform(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),ui(new Ui::mainformClass)
	 // _scanner(new fusionScanner())
{
	
	ui->setupUi(this);
	/*设置mainTab*/
	ui->mainTab->setCurrentIndex(0);///要在setupUi之后
	
}

mainform::~mainform()
{

}



void mainform::on_connectKinect_triggered(){

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
void mainform::on_ToolstartBtn_triggered(){
	viewerTimer=startTimer(0);
	updateTimer=startTimer(33);

	cout<<viewerTimer<<" "<<updateTimer<<endl;
}


void mainform::timerEvent(QTimerEvent *event)
{
// 	if (event->timerId()==viewerTimer)
// 	{
// 		
// 
// 		_capture->grab(_scanner->depth, _scanner->image);
// 
// 		//ui->init_viewer->showImage(_scanner->image );
// 		show_depth(_scanner->depth,ui->init_viewer);
// 	}
// 	else if (event->timerId()==updateTimer)
// 	{
// 		
// 		_scanner->update()
// 		ui->init_viewer->showImage(frame);
// 	}
	_scanner->update();//更新数据

	showInViewer(_scanner->view_host_,ui->fusionViewer);
 	showInViewer(_scanner->image,ui->RGBViewer);
 	showInViewer(_scanner->depth,ui->depthViewer);

	//ui->init_viewer->showImage(_scanner->image );
// 	cout<<"image.channels():"<<_scanner->image.channels()<<endl;
// 	cout<<"view_host_.channels():"<<_scanner->view_host_.channels()<<endl;
	//cv::imshow("Scene", _scanner->view_host_);
	//show_depth(_scanner->depth,ui->init_viewer);
	
}
/*在glview中显示二维数据
params:
	cv::Mat& data
	glViewer *viewer
*/
void mainform::showInViewer(const cv::Mat& data,glViewer *viewer)
{
	
	if (data.channels()==1)
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