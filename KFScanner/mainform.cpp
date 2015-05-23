#include "mainform.h"
#include <QtGui/QDialog>
#include "fusionScanner.h"
#include <string> 

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
	ui.init_toolbox->setCurrentIndex(0);
	resetToDefault();


	/////////////////////////////////////////////////////////////////
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
	ui.delay_slider->setValue(0);
	ui.range_slider->setValue(1500);
	ui.full_rb->setChecked(true);
}


void mainform::on_connectKinect_triggered()
{

	int device = 0;
	int use_default_params=0;
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
	if (use_default_params)
	{
		_scanner = new fusionScanner(*_capture);//����scanner appʵ����ע����һ��ָ��
	}
	else
	{
		_scanner = new fusionScanner(*_capture,setKinfuParams());
		
	}
	
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

kfusion::KinFuParams  mainform::setKinfuParams()
{
	KinFuParams p;
	const int iters[] = {10, 5, 4, 0};
	const int levels = sizeof(iters)/sizeof(iters[0]);//ICP��������

	//�ֱ���640*480
	p.cols = 640;  //pixels
	p.rows = 480;  //pixels
	

	p.intr = Intr(525.f, 525.f, p.cols/2 - 0.5f, p.rows/2 - 0.5f);

	p.volume_dims = Vec3i::all(512);  //number of voxels
	p.volume_size = Vec3f::all(3.f);  //meters

	QString res = to_QString(to_string(static_cast<long long>(p.cols))+"*"+to_string(static_cast<long long>(p.rows)));
	QString dim = to_QString(to_string(static_cast<long long>(p.volume_dims[0]))+" "+to_string(static_cast<long long>(p.volume_dims[1]))+" "+to_string(static_cast<long long>(p.volume_dims[2])));
	QString size = to_QString(to_string(static_cast<long long>(p.volume_size[0]))+" "+to_string(static_cast<long long>(p.volume_size[1]))+" "+to_string(static_cast<long long>(p.volume_size[2])));

	////////////////////////////////////////////////////////
	ui.res_value_label->setText(res);
	ui.dims_label->setText(dim);
	ui.size_label->setText(size);


	p.volume_pose = Affine3f().translate(Vec3f(-p.volume_size[0]/2, -p.volume_size[1]/2, 0.5f));

	p.bilateral_sigma_depth = ui.sigma_depth_sb->value();  //meter
	p.bilateral_sigma_spatial = ui.sigma_spatial_sb->value(); //pixels
	p.bilateral_kernel_size = ui.sigma_k_size_sb->value();     //pixels

	//���������ICP����
	p.icp_truncate_depth_dist = ui.ICP_depthdist_sb->value();        //meters, disabled //�ƺ����˵��ǽ���������
	p.icp_dist_thres = ui.ICP_dist_th_sb->value();                //meters
	p.icp_angle_thres = deg2rad(ui.ICP_angel_th_sb->value()); //radians//�����ǽǶ�
	p.icp_iter_num.assign(iters, iters + levels);

	p.tsdf_min_camera_movement = ui.cam_min_move_sb->value(); //meters, disabled //�����ںϵ���С�����λ��
	p.tsdf_trunc_dist = ui.tsdf_dist_sb->value(); //meters;
	p.tsdf_max_weight = ui.tsdf_max_weight_sb->value();   //frames

	p.raycast_step_factor = ui.raycast_factor_sb->value();  //in voxel sizes
	p.gradient_delta_factor = ui.gradient_factor_sb->value(); //in voxel sizes

	//p.light_pose = p.volume_pose.translation()/4; //meters
	p.light_pose = Vec3f::all(0.f); //meters

	return p;
}
