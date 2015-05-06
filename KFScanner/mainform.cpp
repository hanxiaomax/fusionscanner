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
}

mainform::~mainform()
{

}

void mainform::on_connectKinect_triggered(){

	int device = 0;
	cuda::setDevice (device);//����GPU��0
	cuda::printShortCudaDeviceInfo (device);//��ӡGPU��Ϣ


	//���GPU�ܹ��Ƿ�֧��
	if(cuda::checkIfPreFermiGPU(device))
	{
		cout << endl << "Kinfu is not supported for pre-Fermi GPU architectures, and not built for them by default. Exiting..." << endl;
		return; 
	}

	cout<<"GPU check"<<endl;

	_capture = new OpenNISource();
	_capture->open(0);
	_scanner = new fusionScanner(*_capture);//����scanner appʵ����ע����һ��ָ��
}
void mainform::on_connectlifter_triggered(){
	//viewerTimer=startTimer(0);
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
// 		ui->init_viewer->showImage(_scanner->image );
// 	}
// 	else if (event->timerId()==updateTimer)
// 	{
// 		
// 		_scanner->update()
// 		ui->init_viewer->showImage(frame);
// 	}
	_scanner->update();
	//ui->init_viewer->showImage(_scanner->view_host_);
	ui->init_viewer->showImage(_scanner->image );
	cv::imshow("Scene", _scanner->view_host_);
}