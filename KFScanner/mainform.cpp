#include "mainform.h"
#include <QtGui/QDialog>
#include <QFileDialog>
#include <string> 
#include <QSettings>
#include <QMessageBox>
#include <QTextCodec> 
#include <QTime>
#include <io.h>
#include <pcl/console/time.h>
#include <pcl/surface/marching_cubes_hoppe.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/surface/mls.h>
#include <fstream>
#include <sstream>
#include <kfusion/MCmesh.h>
/*************************************
 *  简要描述: GUI界面逻辑
 ************************************/  
using namespace kfusion;
using namespace std;

void sleep(unsigned int msec);
/*-------------------------------------------* 
*  功能描述: 构造函数完成界面初始化和默认设置
-------------------------------------------*/  
mainform::mainform(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),
	ui(Ui::mainformClass()),//如果ui是对象的话这里其实没有必要，初始化已经完成
	port(new QextSerialPort()),//初始化串口对象
	isFacilityOK(false),//串口初始状态
	isGpuOK(false),//GPU
	isKinectOK(false),//Kinect
	with_normal(true),//保存点云和法线
	cloudFromFile(false),
	pcd_buffer_(new pcl::PointCloud<pcl::PointNormal>())
{
	//////指针初始化
	_scanner = 0;
	_capture = 0;
	sd = 0;
	/////////////////////////////////////////////////
	ui.setupUi(this);
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//设定字符集以显示中文
	/////设置mainTab
	ui.mainTab->setCurrentIndex(0);///要在setupUi之后
	ui.init_toolbox->setCurrentIndex(0);
	setScanToDefault();//设置默认扫描参数
	setkinfuToDefault();//设置默认kinfu参数
	////串口列表相关初始化
	ui.port_list->clear();
	ui.port_list->addItems(findAvailablePort());
	init_scriptList();
	ui.runBtn->setDisabled(true);
	//////////////////////////////////////
	
	updateStateTimer=startTimer(1000);//定时检查并更新设备状态500ms
	
}

mainform::~mainform()
{
	if (_capture)//如果不连接就直接关闭窗口，则_capture不存在
	{
		_capture->release();
	}
	port->close();//断开串口连接
}

/*-------------------------------------* 
*  功能描述: 设置面板上的扫描参数到默认
--------------------------------------*/  
void mainform::setScanToDefault()
{
	ui.delay_slider->setValue(0);
	ui.range_slider->setValue(1500);
}
/*----------------------------------------*
 *  功能描述: 设置面板上的kinfu参数到默认
 ----------------------------------------*/  
void mainform::setkinfuToDefault()
{
	ui.sigma_depth_sb->setValue(0.04);
	ui.sigma_spatial_sb->setValue(4.5);
	ui.sigma_k_size_sb->setValue(7.00);

	ui.ICP_depthdist_sb->setValue(1.10);
	ui.ICP_dist_th_sb->setValue(0.10);
	ui.ICP_angel_th_sb->setValue(30);

	ui.cam_min_move_sb->setValue(0.00);
	ui.tsdf_dist_sb->setValue(0.04);
	ui.tsdf_max_weight_sb->setValue(64.0);//64-->150
	ui.raycast_factor_sb->setValue(0.75);
	ui.gradient_factor_sb->setValue(0.50);
	
}

/*----------------------------------------*
 *  功能描述: 保存点云按钮触发槽函数
 ----------------------------------------*/ 
void mainform::on_actionSaveCloud_triggered()
{
	*pcd_buffer_=_scanner->savePointCloud(ui.ply_check->checkState()==Qt::Checked,ui.pcd_check->checkState()==Qt::Checked);//写入文件
	ui.cloudViewer->setPcdBuffer(pcd_buffer_);
	ui.resultViewer->setPcdBuffer(pcd_buffer_);
	ui.cloudViewer->update();
	ui.resultViewer->update();
}

/*----------------------------------------*
 *  功能描述: 保存点云（按钮）
 ----------------------------------------*/ 
void mainform::on_saveCloudBtn_clicked()
{
	//点云写入pcd_buffer
	*pcd_buffer_=_scanner->savePointCloud(ui.ply_check->checkState()==Qt::Checked,ui.pcd_check->checkState()==Qt::Checked);//写入文件
	//
	ui.cloudViewer->setPcdBuffer(pcd_buffer_);//拷贝pcd_buffer到cloudviewer然后显示
	ui.cloudViewer->update();
	ui.resultViewer->setPcdBuffer(pcd_buffer_);
	ui.resultViewer->setInputCloud(pcd_buffer_);
	ui.resultViewer->update();
}
/*----------------------------------------*
 *  功能描述: 曲面重建按钮
 ----------------------------------------*/ 
void mainform::on_reconsBtn_clicked()
{
	
	runMarchingCube();
	
	QMessageBox::information(NULL, tr("成功"), tr("重建"));
	ui.mesh_viewer->setMeshBuffer(mesh);
	//ui.mesh_viewer->setInputCloud(pcd_buffer_);
	ui.mesh_viewer->update();
	//ui.resultViewer->setPcdBuffer(pcd_buffer_);
	//ui.resultViewer->update();

}
/*----------------------------------------*
 *  功能描述: 保存重建后的曲面
 ----------------------------------------*/ 
void mainform::on_savePLYmeshBtn_clicked()
{
	if (mesh.polygons.size()>0)
	{
		QString fileName;  
		fileName = QFileDialog::getSaveFileName(this,  
			tr("保存mesh"), "", tr(" (*.ply)"));  
		if (fileName.size()>0)
			savePLYFile(fileName.toStdString(),mesh);
	}
	else
		QMessageBox::information(NULL, tr("警告"), tr("没有可以用来输出的mesh"));
}
void mainform::on_openMeshBtn_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this,tr("打开mesh文件"),".",tr("*.ply"));
	if(!filename.isEmpty())
	{	
		mesh.polygons.clear();
		cout<<"open:"<<filename.toStdString()<<endl;
		loadPLYFile(filename.toStdString(),mesh);

		cout<<"opened!"<<endl;
		ui.mesh_viewer->setMeshBuffer(mesh);
		ui.mesh_viewer->update();
	}
	
}

/*----------------------------------------*
 *  功能描述: 重置kinfu参数按钮触发槽函数
 ----------------------------------------*/ 
void mainform::on_action_ResetKinFuParams_triggered()
{
	setkinfuToDefault();
}
/*----------------------------------------*
 *  功能描述: 重置扫描参数按钮触发槽函数
 ----------------------------------------*/ 
void mainform::on_action_ResetScanParams_triggered()
{
	setScanToDefault();
}
/*----------------------------------------*
 *  功能描述: Kinect按钮触发槽函数
 ----------------------------------------*/ 
void mainform::on_connectKinect_triggered()
{
	bool use_default_params = false;
	///设置摄像机参数
	kinectParams kinectparams;
	kinectparams.beginRange = 0;
	kinectparams.endRange = ui.range_slider->value();
	///检查显卡，若支持，
	if(checkGPUdevice())
	{
		isGpuOK=true;
		_capture = new OpenNISource(0,kinectparams);//初始化摄像机
		if (use_default_params){
			_scanner = new fusionScanner(*_capture);//创建scanner app实例，注意是一个指针
		}
		else{
			_scanner = new fusionScanner(*_capture,setKinfuParams());
		}
		isKinectOK=true;
	}
	else
	{
//TODO：显卡不支持情况下不应该直接退出
		isGpuOK=false;
		
	}
}
/*----------------------------------------*
 *  功能描述: 开始录制按钮触发槽函数
 ----------------------------------------*/ 
void mainform::on_ToolstartBtn_triggered()
{
	unsigned int delay=ui.delay_slider->value()*1000;//毫秒变为秒
	_scanner->fusionStart();
	_scanner->cameraStart();
	
	updateTimer=startTimer(33);//viewer定时器，33ms触发一次
	delayTimer=startTimer(delay);//fusionstart延时启动定时器，触发一次
}

/*----------------------------------------*
 *  功能描述: 停止录制按钮触发槽函数
 ----------------------------------------*/ 
void mainform::on_ToolstopBtn_triggered()
{
	_scanner->fusionHold();
	_scanner->cameraHold();
}
/*----------------------------------------*
 *  功能描述: 复位摄像机按钮触发槽函数
 ----------------------------------------*/ 
void mainform::on_TooldeleteBtn_triggered()
{

	_scanner->fusionReset();
	//ui.fusionViewer->updateScene();//只有在派生类中才可以通过派生类对象访问基类的protected成员。
	//showInViewer(_scanner->view_host_,ui.fusionViewer);
}

/*----------------------------------------*
 *  功能描述: 扫描串口按钮触发槽函数
 ----------------------------------------*/ 
void mainform::on_scanPortBtn_clicked()
{
	QStringList comList = findAvailablePort();//返回全部可用串口
	if (comList.empty()){
		QMessageBox::information(NULL, tr("警告"), tr("没有可用的端口，请检查蓝牙适配器是否插入"));
	}
	else
	{
		ui.port_list->clear();
		ui.port_list->addItems(comList);
	}
	
}
/*----------------------------------------*
 *  功能描述: 连接串口按钮触发槽函数
 ----------------------------------------*/ 
void mainform::on_connectPortBtn_clicked()
{
	QString port_name = ui.port_list->currentText();//获取选择的内容COM13
	QString m_port = port_name.right(port_name.length()-3);//截取数字部分
	if(m_port.toInt()>9)//10以上的端口要加一个前缀
	{
		QString prefix = "\\\\.\\";
		prefix.append(port_name);
		port->setPortName(prefix);
	}
	else
	{
		port->setPortName(port_name);
	}
	if (isFacilityOK)
	{
		int r = QMessageBox::warning(this,tr("警告"), tr("确定要断开连接吗？"),QMessageBox::Yes|QMessageBox::No);
		if(r==QMessageBox::Yes)
		{
			port->close();
			isFacilityOK = false;
			ui.portStatus->setText(tr("未连接"));
			ui.connectPortBtn->setText(tr("连接端口"));
			ui.portStatus->setStyleSheet("background-color:rgb(255,99,71);color:rgb(255,255,255)");
			port->write("~PC");
			ui.port_list->setDisabled(false);
			ui.runBtn->setDisabled(true);

		}
	}
	else
	{
		if(!port->open(QIODevice::ReadWrite))
			QMessageBox::information(this, tr("警告"), tr("无法打开端口，请检查连接情况或重新扫描端口"));
		else
		{
			port->setBaudRate(BAUD57600);//波特率9600
			port->setStopBits(STOP_1);//1位停止位
			port->setDataBits(DATA_8);//8位数据位
			port->setParity(PAR_NONE);//奇偶校验设置
			ui.port_list->setDisabled(true);
			ui.portStatus->setText(tr("已连接"));
			ui.portStatus->setStyleSheet("background-color:rgb(0,255,0)");
			ui.connectPortBtn->setText(tr("关闭端口"));
			isFacilityOK = true;
			
			port->write("PC");
			//Serital_Timer->start(100);
			ui.runBtn->setDisabled(false);
		}
	}
}

/*----------------------------------------*
 *  功能描述: 运动脚本管理按钮触发槽函数
 ----------------------------------------*/ 
void mainform::on_newScriptBtn_clicked()
{
	if (!sd)
		sd = new script_Dialog(this);
	///////
	connect(sd,SIGNAL(onNewScriptBtn(const QString &)),this,SLOT(addCombox(QString)));//必须先实现sd才能连接
	connect(sd,SIGNAL(onDeleteBtn(int)),this,SLOT(deleteCombox(int)));//必须先实现sd才能连接


	sd->show();
	sd->raise();
	sd->activateWindow();
	///////////////////////////
	//如果是模态的窗口，在这里重新初始化init_scriptList();也是可以的
}


void mainform::on_resetMachineBtn_clicked()
{
	port->write("RUN");
	sleep(100);
	port->write("R1V150L30T100");

}
/*----------------------------------------*
 *  功能描述: 定时器事件处理函数
 *  参数：QTimerEvent *event
 ----------------------------------------*/ 
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
	if(event->timerId()==updateStateTimer)
		ui.init_viewer->updateStates(isFacilityOK,isGpuOK,isKinectOK);
}

/*----------------------------------------*
 *  功能描述: 在Viewer中显示二维图像
 *  参数：data		图像数据
 *  参数：*viewer	glviewer控件
 ----------------------------------------*/ 
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




/*---------------------------------------------*
 *  功能描述: 从面板获取kinfu参数
 *  返回值：kfusion::KinFuParams类型
 --------------------------------------------*/ 
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

/*---------------------------------------------*
 *  功能描述:	检查GPU设备
 *  返回值：	可以使用则返回1，否则返回0
 --------------------------------------------*/ 
int mainform::checkGPUdevice()
{
	int device = 0;

	cuda::setDevice (device);//设置GPU：0
	//cuda::printShortCudaDeviceInfo (device);//打印GPU信息

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
/*---------------------------------------------*
 *  功能描述: 设置GUP信息到面板
 --------------------------------------------*/ 
void mainform::setGPUinfo()
{
	kf::cuda::CUDAinfo p = kf::cuda::getShortCudaDeviceInfo(0);
	ui.device_info->setText(to_QString(p.device_name));
	ui.ram_info->setText(to_QString(to_string(static_cast<long long>(p.RAM))));
	ui.core_info->setText(to_QString(to_string(static_cast<long long>(p.core))));
	ui.computeCap->setText(to_QString(p.computerCap));
	ui.driver_info->setText(to_QString(p.driver));
}


/*---------------------------------------------*
 *  功能描述: 查找可以使用的串口
 *	返回值	：包含所有可以串口名的列表
 --------------------------------------------*/ 
QStringList mainform::findAvailablePort()
{
	QString path="HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM";
	QSettings *settings=new QSettings(path,QSettings::NativeFormat);
	
	QStringList key=settings->allKeys();
	QStringList comlist ;

	int kk = key.size();
	comlist.clear();
	for(int i=0;i<kk;i++)
	{
		comlist << _getCom(i,"value");
	}
	return comlist;
}

QString mainform::_getCom(int index ,QString keyorvalue)
{
	QString commresult="";
	QString strkey="HARDWARE\\DEVICEMAP\\SERIALCOMM";//子键路径
	int a=strkey.toWCharArray(subkey);
	subkey[a]=L'\0';
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,subkey,0,KEY_READ|KEY_QUERY_VALUE,&hKey)!=0)
	{
		QString error="Cannot open regedit!";
	}

	QString keymessage="";//键名
	QString message="";
	QString valuemessage="";//键值
	indexnum=index;//要读取键值的索引号

	keysize=sizeof(keyname);
	valuesize=sizeof(keyvalue);

	if(::RegEnumValue(hKey,indexnum,keyname,&keysize,0,&type,(BYTE*)keyvalue,&valuesize)==0)
	{
		//读取键名
		for(int i=0;i<keysize;i++)
		{
			message=QString::fromStdWString(keyname);
			keymessage.append(message);
		}
		//读取键值
		for(int j=0;j<valuesize;j++)
		{
			if(keyvalue[j]!=0x00)
			{
				valuemessage.append(keyvalue[j]);
			}
		}

		if(keyorvalue=="key")
		{
			commresult=keymessage;
		}
		if(keyorvalue=="value")
		{
			commresult=valuemessage;
		}
	}
	else
	{
		commresult="nokey";
	}
	::RegCloseKey(hKey);//关闭注册表

	return commresult;
}

/*------------------------------------------------------------------*
 *  功能描述: 查找scripts文件夹下全部文件名，并初始化combo box
 *  参考资料：http://blog.csdn.net/xuejiren/article/details/37040827
 -------------------------------------------------------------------*/ 
void mainform::init_scriptList()
{
	vector<string> files; 
	long   hFile   =   0;  
	string path = "scripts/";//要查找的目录
	struct _finddata_t fileinfo;  //结构体，存放文件信息
	string p;  
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{  
			files.push_back(fileinfo.name);//把找到的文件名加入到files中

		}while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile);  
	}
	ui.script_combox->clear();
	for (int i = 0 ; i<files.size() ; i++)//一次添加到combo box
	{
		if (!(files[i]==".."||files[i]=="."))//跳过目录..,保留.
			ui.script_combox->addItem(files[i].c_str());
	}
}

/*------------------------------------------------------------------*
 *  功能描述:	添加新建的文件到combox
 *  参数：		从信号传递过来的文件名
 -------------------------------------------------------------------*/ 
void mainform::addCombox(QString filename)
{
	ui.script_combox->addItem(filename);
}

/*------------------------------------------------------------------*
 *  功能描述:	从combox删除
 *  参数：		从信号传递过来的文件名
 -------------------------------------------------------------------*/ 
void mainform::deleteCombox(int index)
{
	ui.script_combox->removeItem(index);
}
/*------------------------------------------------------------------*
 *  功能描述:	离群点过滤按钮
 *  参数：		从信号传递过来的文件名
 -------------------------------------------------------------------*/ 
void mainform::on_outremoveBtn_clicked()
{	
		pcl::PointCloud<pcl::PointNormal>::Ptr temp(new pcl::PointCloud<pcl::PointNormal>);

		int mean_k = ui.sb_meank->value();
		float std_dev = ui.sb_std_dev->value();
		OutRemover or(mean_k,std_dev);

		if(pcd_buffer_->size()>0)
		{
			or.execute(pcd_buffer_,*temp);//执行滤波
			pcd_buffer_= temp;
			ui.resultViewer->setPcdBuffer(pcd_buffer_);//对滤波后结果进行可视化
			ui.resultViewer->update();
		}
		else
			QMessageBox::information(NULL, tr("警告"), tr("没有可以用来处理的点云"));
}

void mainform::on_cloudOpenBtn_clicked()
{
	pcd_buffer_->clear();//清空点云buffer，否则会出现叠加
	QString filename = QFileDialog::getOpenFileName(this,tr("打开点云文件"),".",tr("*.ply"));
	if(!filename.isEmpty())
	{	
		PLYFilereader reader;
		
		if (reader.loadPlyCloud(filename.toStdString(),*pcd_buffer_))
		{
			cout<<"open : "<<filename.toStdString()<<endl;
		}
		///if(reader.readToVertexes(filename.toStdString(),*input_cloud,pcd_buffer,false))//读到主界面的pcd_buffer中
			
		else
			cout<<"can not open : "<<filename.toStdString()<<endl;
	}
	ui.resultViewer->setPcdBuffer(pcd_buffer_);
	ui.resultViewer->setInputCloud(pcd_buffer_);
	cout<<"main form input_cloud.size()="<<pcd_buffer_->size()<<endl;
	ui.resultViewer->update();
}
void mainform::on_cloudExportBtn_clicked()
{
	if (pcd_buffer_->size()>0)
	{
		QString fileName;  
		fileName = QFileDialog::getSaveFileName(this,  
			tr("保存点云"), "", tr(" (*.ply)"));  
		if (fileName.size()>0)
		{
			PLYFilewriter w;
			w.write(fileName.toStdString(),*pcd_buffer_,false);
		}
	}
	else
		QMessageBox::information(NULL, tr("警告"), tr("没有可以用来输出的点云"));	
}

//////////////////////////////////////////////////
//毫秒级别延时函数
void sleep(unsigned int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while( QTime::currentTime() < dieTime )
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void mainform::runMarchingCube()
{
	float iso_level = ui.iso_value->value();//0.0
	int grid_res = ui.res_value->value();//70
	float extend_percentage = ui.percentage_value->value();//0.0
	float off_surface_displacement =  ui.off_value->value();//0.01

	//MarchingCubes<PointNormal> *mc;
	//mc = new MarchingCubesHoppe<PointNormal> ();

	mesh::MCmesh *mc;
	mc = new mesh::MCmesh();
	
	mc->setIsoLevel (iso_level);
	mc->setGridRes(grid_res,grid_res,grid_res);
	mc->setPercentage(extend_percentage);
	
	mc->setInputCloud (pcd_buffer_);

	TicToc tt;
	tt.tic ();

	print_highlight ("重建中... \n");
	mc->run(mesh);

	delete mc;
}
void mainform::runMLS()
{
	pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointNormal> mls;
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointNormal>::Ptr mls_points;
	mls.setComputeNormals (true);

	// Set parameters
	mls.setInputCloud (pcd_xyz);
	mls.setPolynomialFit (true);
	mls.setSearchMethod (tree);
	mls.setSearchRadius (0.03);

	// Reconstruct
	mls.process (*mls_points);
}

