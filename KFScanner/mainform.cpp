#include "mainform.h"
#include <QtGui/QDialog>
#include "fusionScanner.h"


using namespace kfusion;
using namespace std;


mainform::mainform(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	//ui(Ui::mainformClass())//���ui�Ƕ���Ļ�������ʵû�б�Ҫ����ʼ���Ѿ����

{
	/*ָ���ʼ��*/
	_scanner=NULL;
	_capture=NULL;

	ui.setupUi(this);
	/*����mainTab*/
	ui.mainTab->setCurrentIndex(0);///Ҫ��setupUi֮��
	connect(ui.defaultBtn,SIGNAL(clicked()),this,SLOT(resetToDefault()));
	connect(ui.showCloudBtn,SIGNAL(clicked()),this,SLOT(onShowCloudBtn()));//�ȼ���on_ShowCloudBtn_clicked(),���Բ۵��������������������ᷢ�������ź�

}

mainform::~mainform()
{
	if (_capture)//��������Ӿ�ֱ�ӹرմ��ڣ���_capture������
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
void mainform::on_ToolstartBtn_triggered()
{
	unsigned int delay=ui.delay_slider->value()*1000;//�����Ϊ��
	updateTimer=startTimer(33);//viewer��ʱ����33ms����һ��
	delayTimer=startTimer(delay);//fusionstart��ʱ������ʱ��������һ��
}

//ֹͣɨ��:ֹͣ����fusion����
void mainform::on_ToolstopBtn_triggered()
{
	_scanner->fusionHold();
}

void mainform::on_TooldeleteBtn_triggered()
{

	_scanner->fusionReset();
	//ui.fusionViewer->updateScene();//ֻ�����������вſ���ͨ�������������ʻ����protected��Ա��
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
		_scanner->update();//��������
		if(!_scanner->view_host_.empty())//view_host_��run()֮ǰ�ǿյģ���ʾ�����
		{	
			showInViewer(_scanner->view_host_,ui.fusionViewer);
		}	
		showInViewer(_scanner->image,ui.RGBViewer);
		showInViewer(_scanner->depth,ui.depthViewer);
	}
	if (event->timerId()==delayTimer)
	{
		killTimer(delayTimer);//����һ�κ�ص���ʱ��
		_scanner->fusionStart();
	}

}
/*��glview����ʾ��ά����
params:
	cv::Mat& data
	glViewer *viewer
*/
void mainform::showInViewer(const cv::Mat& data,glViewer *viewer)
{
	if (data.channels()==1)//��������ݽ��б任
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

