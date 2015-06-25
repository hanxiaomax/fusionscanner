#include "mainform.h"
#include <QtGui/QDialog>
#include <string> 
#include <QSettings>
#include <QMessageBox>
#include <QTextCodec> 
#include <QTime>
#include <io.h>
/*************************************
 *  ��Ҫ����: GUI�����߼�
 ************************************/  
using namespace kfusion;
using namespace std;

void sleep(unsigned int msec);

/*-------------------------------------------* 
*  ��������: ���캯����ɽ����ʼ����Ĭ������
-------------------------------------------*/  
mainform::mainform(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),
	ui(Ui::mainformClass()),//���ui�Ƕ���Ļ�������ʵû�б�Ҫ����ʼ���Ѿ����
	port(new QextSerialPort()),//��ʼ�����ڶ���
	isOpen(false)//���ڳ�ʼ״̬
{
	//////ָ���ʼ��
	_scanner = 0;
	_capture = 0;
	sd = 0;
	/////////////////////////////////////////////////
	ui.setupUi(this);
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//�趨�ַ�������ʾ����
	/////����mainTab
	ui.mainTab->setCurrentIndex(0);///Ҫ��setupUi֮��
	ui.init_toolbox->setCurrentIndex(0);
	setScanToDefault();//����Ĭ��ɨ�����
	setkinfuToDefault();//����Ĭ��kinfu����
	////�����б���س�ʼ��
	ui.port_list->clear();
	ui.port_list->addItems(findAvailablePort());
	init_scriptList();
	ui.runBtn->setDisabled(true);
	//////////////////////////////////////
	
	//Serital_Timer = new QTimer();
	
}

mainform::~mainform()
{
	if (_capture)//��������Ӿ�ֱ�ӹرմ��ڣ���_capture������
	{
		_capture->release();
	}
	port->close();//�Ͽ���������
}

/*-------------------------------------* 
*  ��������: ��������ϵ�ɨ�������Ĭ��
--------------------------------------*/  
void mainform::setScanToDefault()
{
	ui.delay_slider->setValue(0);
	ui.range_slider->setValue(1500);
}
/*----------------------------------------*
 *  ��������: ��������ϵ�kinfu������Ĭ��
 ----------------------------------------*/  
void mainform::setkinfuToDefault()
{
	ui.sigma_depth_sb->setValue(0.04);
	ui.sigma_spatial_sb->setValue(4.5);
	ui.sigma_k_size_sb->setValue(7.00);

	ui.ICP_depthdist_sb->setValue(0.00);
	ui.ICP_dist_th_sb->setValue(0.10);
	ui.ICP_angel_th_sb->setValue(30);

	ui.cam_min_move_sb->setValue(0.00);
	ui.tsdf_dist_sb->setValue(0.04);
	ui.tsdf_max_weight_sb->setValue(64.0);//64-->150
	ui.raycast_factor_sb->setValue(0.75);
	ui.gradient_factor_sb->setValue(0.50);

}

/*----------------------------------------*
 *  ��������: ������ư�ť�����ۺ���
 ----------------------------------------*/ 
void mainform::on_actionSaveCloud_triggered()
{
	_scanner->take_cloud(true);
}
/*----------------------------------------*
 *  ��������: ����kinfu������ť�����ۺ���
 ----------------------------------------*/ 
void mainform::on_action_ResetKinFuParams_triggered()
{
	setkinfuToDefault();
}
/*----------------------------------------*
 *  ��������: ����ɨ�������ť�����ۺ���
 ----------------------------------------*/ 
void mainform::on_action_ResetScanParams_triggered()
{
	setScanToDefault();
}
/*----------------------------------------*
 *  ��������: Kinect��ť�����ۺ���
 ----------------------------------------*/ 
void mainform::on_connectKinect_triggered()
{
	bool use_default_params = false;
	///�������������
	kinectParams kinectparams;
	kinectparams.beginRange = 0;
	kinectparams.endRange = ui.range_slider->value();
	///����Կ�����֧�֣�
	if(checkGPUdevice())
	{
		_capture = new OpenNISource(0,kinectparams);//��ʼ�������
		if (use_default_params){
			_scanner = new fusionScanner(*_capture);//����scanner appʵ����ע����һ��ָ��
		}
		else{
			_scanner = new fusionScanner(*_capture,setKinfuParams());
		}
	}
	else
	{
//TODO���Կ���֧������²�Ӧ��ֱ���˳�
		return;
	}
}
/*----------------------------------------*
 *  ��������: ��ʼ¼�ư�ť�����ۺ���
 ----------------------------------------*/ 
void mainform::on_ToolstartBtn_triggered()
{
	unsigned int delay=ui.delay_slider->value()*1000;//�����Ϊ��
	updateTimer=startTimer(33);//viewer��ʱ����33ms����һ��
	delayTimer=startTimer(delay);//fusionstart��ʱ������ʱ��������һ��
}

/*----------------------------------------*
 *  ��������: ֹͣ¼�ư�ť�����ۺ���
 ----------------------------------------*/ 
void mainform::on_ToolstopBtn_triggered()
{
	_scanner->fusionHold();
}
/*----------------------------------------*
 *  ��������: ��λ�������ť�����ۺ���
 ----------------------------------------*/ 
void mainform::on_TooldeleteBtn_triggered()
{

	_scanner->fusionReset();
	//ui.fusionViewer->updateScene();//ֻ�����������вſ���ͨ�������������ʻ����protected��Ա��
	//showInViewer(_scanner->view_host_,ui.fusionViewer);
}

/*----------------------------------------*
 *  ��������: ɨ�贮�ڰ�ť�����ۺ���
 ----------------------------------------*/ 
void mainform::on_scanPortBtn_clicked()
{
	QStringList comList = findAvailablePort();//����ȫ�����ô���
	if (comList.empty()){
		QMessageBox::information(NULL, tr("����"), tr("û�п��õĶ˿ڣ����������������Ƿ����"));
	}
	else
	{
		ui.port_list->clear();
		ui.port_list->addItems(comList);
	}
	
}
/*----------------------------------------*
 *  ��������: ���Ӵ��ڰ�ť�����ۺ���
 ----------------------------------------*/ 
void mainform::on_connectPortBtn_clicked()
{
	QString port_name = ui.port_list->currentText();//��ȡѡ�������COM13
	QString m_port = port_name.right(port_name.length()-3);//��ȡ���ֲ���
	if(m_port.toInt()>9)//10���ϵĶ˿�Ҫ��һ��ǰ׺
	{
		QString prefix = "\\\\.\\";
		prefix.append(port_name);
		port->setPortName(prefix);
	}
	else
	{
		port->setPortName(port_name);
	}
	if (isOpen)
	{
		int r = QMessageBox::warning(this,tr("����"), tr("ȷ��Ҫ�Ͽ�������"),QMessageBox::Yes|QMessageBox::No);
		if(r==QMessageBox::Yes)
		{
			port->close();
			isOpen = false;
			ui.portStatus->setText(tr("δ����"));
			ui.connectPortBtn->setText(tr("���Ӷ˿�"));
			ui.portStatus->setStyleSheet("background-color:rgb(255,99,71);color:rgb(255,255,255)");
			port->write("~PC");
			ui.port_list->setDisabled(false);
			ui.runBtn->setDisabled(true);

		}
	}
	else
	{
		if(!port->open(QIODevice::ReadWrite))
			QMessageBox::information(this, tr("����"), tr("�޷��򿪶˿ڣ������������������ɨ��˿�"));
		else
		{
			port->setBaudRate(BAUD57600);//������9600
			port->setStopBits(STOP_1);//1λֹͣλ
			port->setDataBits(DATA_8);//8λ����λ
			port->setParity(PAR_NONE);//��żУ������
			ui.port_list->setDisabled(true);
			ui.portStatus->setText(tr("������"));
			ui.portStatus->setStyleSheet("background-color:rgb(0,255,0)");
			ui.connectPortBtn->setText(tr("�رն˿�"));
			isOpen = true;
			port->write("PC");
			//Serital_Timer->start(100);
			ui.runBtn->setDisabled(false);
		}
	}
}

/*----------------------------------------*
 *  ��������: �˶��ű�����ť�����ۺ���
 ----------------------------------------*/ 
void mainform::on_newScriptBtn_clicked()
{
	if (!sd)
		sd = new script_Dialog(this);
	///////
	connect(sd,SIGNAL(onNewScriptBtn(const QString &)),this,SLOT(addCombox(QString)));//������ʵ��sd��������
	connect(sd,SIGNAL(onDeleteBtn(int)),this,SLOT(deleteCombox(int)));//������ʵ��sd��������


	sd->show();
	sd->raise();
	sd->activateWindow();
	///////////////////////////
	//�����ģ̬�Ĵ��ڣ����������³�ʼ��init_scriptList();Ҳ�ǿ��Ե�
}
void mainform::on_resetMachineBtn_clicked()
{
	port->write("RUN");
	sleep(100);
	port->write("R1V150L30T100");

}
/*----------------------------------------*
 *  ��������: ��ʱ���¼�������
 *  ������QTimerEvent *event
 ----------------------------------------*/ 
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

/*----------------------------------------*
 *  ��������: ��Viewer����ʾ��άͼ��
 *  ������data		ͼ������
 *  ������*viewer	glviewer�ؼ�
 ----------------------------------------*/ 
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




/*---------------------------------------------*
 *  ��������: ������ȡkinfu����
 *  ����ֵ��kfusion::KinFuParams����
 --------------------------------------------*/ 
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


void mainform::setScanParams(kinectParams &kp)
{

}

/*---------------------------------------------*
 *  ��������:	���GPU�豸
 *  ����ֵ��	����ʹ���򷵻�1�����򷵻�0
 --------------------------------------------*/ 
int mainform::checkGPUdevice()
{
	int device = 0;

	cuda::setDevice (device);//����GPU��0
	//cuda::printShortCudaDeviceInfo (device);//��ӡGPU��Ϣ

	//���GPU�ܹ��Ƿ�֧��
	if(cuda::checkIfPreFermiGPU(device))
	{
		cout << endl << "GPU �ܹ���֧�֣��˳�" << endl;
		return 0; 
	}

	cout<<"GPU ������--֧��"<<endl;
	setGPUinfo();
	return 1;
}
/*---------------------------------------------*
 *  ��������: ����GUP��Ϣ�����
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
 *  ��������: ���ҿ���ʹ�õĴ���
 *	����ֵ	���������п��Դ��������б�
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
	QString strkey="HARDWARE\\DEVICEMAP\\SERIALCOMM";//�Ӽ�·��
	int a=strkey.toWCharArray(subkey);
	subkey[a]=L'\0';
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,subkey,0,KEY_READ|KEY_QUERY_VALUE,&hKey)!=0)
	{
		QString error="Cannot open regedit!";
	}

	QString keymessage="";//����
	QString message="";
	QString valuemessage="";//��ֵ
	indexnum=index;//Ҫ��ȡ��ֵ��������

	keysize=sizeof(keyname);
	valuesize=sizeof(keyvalue);

	if(::RegEnumValue(hKey,indexnum,keyname,&keysize,0,&type,(BYTE*)keyvalue,&valuesize)==0)
	{
		//��ȡ����
		for(int i=0;i<keysize;i++)
		{
			message=QString::fromStdWString(keyname);
			keymessage.append(message);
		}
		//��ȡ��ֵ
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
	::RegCloseKey(hKey);//�ر�ע���

	return commresult;
}

/*------------------------------------------------------------------*
 *  ��������: ����scripts�ļ�����ȫ���ļ���������ʼ��combo box
 *  �ο����ϣ�http://blog.csdn.net/xuejiren/article/details/37040827
 -------------------------------------------------------------------*/ 
void mainform::init_scriptList()
{
	vector<string> files; 
	long   hFile   =   0;  
	string path = "scripts/";//Ҫ���ҵ�Ŀ¼
	struct _finddata_t fileinfo;  //�ṹ�壬����ļ���Ϣ
	string p;  
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{  
			files.push_back(fileinfo.name);//���ҵ����ļ������뵽files��

		}while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile);  
	}
	ui.script_combox->clear();
	for (int i = 0 ; i<files.size() ; i++)//һ����ӵ�combo box
	{
		if (!(files[i]==".."||files[i]=="."))//����Ŀ¼..,����.
			ui.script_combox->addItem(files[i].c_str());
	}
}

/*------------------------------------------------------------------*
 *  ��������:	����½����ļ���combox
 *  ������		���źŴ��ݹ������ļ���
 -------------------------------------------------------------------*/ 
void mainform::addCombox(QString filename)
{
	ui.script_combox->addItem(filename);
}

/*------------------------------------------------------------------*
 *  ��������:	��comboxɾ��
 *  ������		���źŴ��ݹ������ļ���
 -------------------------------------------------------------------*/ 
void mainform::deleteCombox(int index)
{
	ui.script_combox->removeItem(index);
}
//////////////////////////////////////////////////
//���뼶����ʱ����
void sleep(unsigned int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while( QTime::currentTime() < dieTime )
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

