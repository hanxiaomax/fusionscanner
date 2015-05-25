#include "mainform.h"
#include <QtGui/QDialog>
#include <string> 

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
	ui.init_toolbox->setCurrentIndex(0);
	setScanToDefault();
	setkinfuToDefault();

	/////////////////////////////////////////////////////////////////
	connect(ui.showCloudBtn,SIGNAL(clicked()),this,SLOT(onShowCloudBtn()));//等价于on_ShowCloudBtn_clicked(),所以槽的命名不能是这个，否则会发射两次信号

}

mainform::~mainform()
{
	if (_capture)//如果不连接就直接关闭窗口，则_capture不存在
	{
		_capture->release();
	}
	
}

void mainform::setScanToDefault()
{
	ui.delay_slider->setValue(0);
	ui.range_slider->setValue(1500);
	ui.full_rb->setChecked(true);
	ui.speed_sb->setValue(50);
	ui.a_speed_sb->setValue(50);
	ui.segment_sb->setValue(3);
	ui.R_segment_sb->setValue(1);

// 	ui.speed->setText("222");
// 	ui.angular_speed->setText("222");
// 	ui.segment->setText("222");
	//ui.R_segement->setText();

	
}

void mainform::setkinfuToDefault()
{
	ui.sigma_depth_sb->setValue(0.04);
	ui.sigma_spatial_sb->setValue(4.5);
	ui.sigma_k_size_sb->setValue(7.00);

	ui.ICP_depthdist_sb->setValue(0.00);
	ui.ICP_dist_th_sb->setValue(0.10);
	ui.ICP_angel_th_sb->setValue(0.52);

	ui.cam_min_move_sb->setValue(0.00);
	ui.tsdf_dist_sb->setValue(0.04);
	ui.tsdf_max_weight_sb->setValue(64.0);
	ui.raycast_factor_sb->setValue(0.75);
	ui.gradient_factor_sb->setValue(0.50);

}

void mainform::on_connectKinect_triggered()
{
	bool use_default_params = false;
	kinectParams p;
	p.beginRange = 0;
	p.endRange = ui.range_slider->value();
	if(checkGPUdevice())
	{
		//_capture = new OpenNISource(0,p);
		//_capture->open(0);
		_capture = new OpenNISource;
		_capture->open(0);
		if (use_default_params)
		{
			_scanner = new fusionScanner(*_capture);//创建scanner app实例，注意是一个指针
		}
		else
		{
			_scanner = new fusionScanner(*_capture,setKinfuParams());

		}
	}
	else
	{
		return;
	}
	
	
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

void mainform::on_action_ResetKinFuParams_triggered()
{
	setkinfuToDefault();
}
void mainform::on_action_ResetScanParams_triggered()
{
	setScanToDefault();
}

kfusion::KinFuParams  mainform::setKinfuParams()
{
	KinFuParams p;
	const int iters[] = {10, 5, 4, 0};
	const int levels = sizeof(iters)/sizeof(iters[0]);//ICP迭代层数

	//分辨率640*480
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

	//迭代最近点ICP参数
	p.icp_truncate_depth_dist = ui.ICP_depthdist_sb->value();        //meters, disabled //似乎过滤的是近处的数据
	p.icp_dist_thres = ui.ICP_dist_th_sb->value();                //meters
	p.icp_angle_thres = deg2rad(ui.ICP_angel_th_sb->value()); //radians//参数是角度
	p.icp_iter_num.assign(iters, iters + levels);

	p.tsdf_min_camera_movement = ui.cam_min_move_sb->value(); //meters, disabled //进行融合的最小摄像机位移
	p.tsdf_trunc_dist = ui.tsdf_dist_sb->value(); //meters;
	p.tsdf_max_weight = ui.tsdf_max_weight_sb->value();   //frames

	p.raycast_step_factor = ui.raycast_factor_sb->value();  //in voxel sizes
	p.gradient_delta_factor = ui.gradient_factor_sb->value(); //in voxel sizes

	//p.light_pose = p.volume_pose.translation()/4; //meters
	p.light_pose = Vec3f::all(0.f); //meters

	return p;
}


void mainform::setScanParams(kinectParams &kp)
{

}

int mainform::checkGPUdevice()
{
	int device = 0;

	cuda::setDevice (device);//设置GPU：0
	cuda::printShortCudaDeviceInfo (device);//打印GPU信息

	//检查GPU架构是否支持
	if(cuda::checkIfPreFermiGPU(device))
	{
		cout << endl << "GPU 架构不支持，退出" << endl;
		return 0; 
	}

	cout<<"GPU 检查完毕--支持"<<endl;
	setGPUinfo();
	return 1;
}

void mainform::setGPUinfo()
{
	kf::cuda::CUDAinfo p = kf::cuda::getShortCudaDeviceInfo(0);
	ui.device_info->setText(to_QString(p.device_name));
	ui.ram_info->setText(to_QString(to_string(static_cast<long long>(p.RAM))));
	ui.core_info->setText(to_QString(to_string(static_cast<long long>(p.core))));
	ui.driver_info->setText(to_QString(p.driver));

}