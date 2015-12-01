#ifndef MAINFORM_H
#define MAINFORM_H
#include <QtGui/QMainWindow>
#include "ui_mainform.h"
#include "script_management.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <kfusion/kinfu.hpp>
#include <io/capture.hpp>
#include <iostream>
#include <fstream>
#include "fusionScanner.h"//包含cloudIO模块
#include <QTimer>
#include "3rdparty/qextserialport/qextserialport.h"//第三方串口库
#include <kfusion\OutRemover.h>


class mainform : public QMainWindow
{
	Q_OBJECT

public:
	mainform(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainform();

private:
	Ui::mainformClass ui;//在类内部使用，此时已经构造了对象ui，完成了初始化（需要构造函数支持）
	script_Dialog * sd;

	fusionScanner*  _scanner;//不一定会用到，且不是参数，声明为指针
	OpenNISource* _capture;//不一定会用到，且不是参数，声明为指针

	QextSerialPort * port;
	int updateTimer;
	int delayTimer;
	int updateStateTimer;
	//QTimer *delayTimer;//一定会用到，且不是参数，应该声明为对象，但是QTimer声明了一个private类型的拷贝构造函数，防止以传值的方式使用，同时也阻止了值初始化。《TIC P.518》
	QTimer *Serital_Timer;
	QStringList m_listCommand;  //待发送的命令
	wchar_t subkey[80];
	wchar_t keyname[256]; //键名数组
	char keyvalue[256];  //键值数组
	int indexnum;
	DWORD keysize,type,valuesize;
	HKEY hKey;
	cv::Mat frame;
	bool with_normal;
	bool cloudFromFile;
	bool isKinectOK;
	bool isFacilityOK;
	bool isGpuOK;
	
	vertexes pcd_buffer;
	pcl::PointCloud<pcl::PointNormal> input_cloud;
	

private slots:
	//////////////////工具栏//////////////////////
	void on_connectKinect_triggered();//连接kinect设备并检查gpu
	void on_ToolstartBtn_triggered();//启动扫描
	void on_ToolstopBtn_triggered();//停止扫描
	void on_TooldeleteBtn_triggered();//软件复位
	void on_actionSaveCloud_triggered();//保存点云
	void on_action_ResetKinFuParams_triggered();//重置kinfu参数
	void on_action_ResetScanParams_triggered();//重置扫描参数
	//////////////////按钮//////////////////////
	void on_scanPortBtn_clicked();
	void on_connectPortBtn_clicked();
	void on_newScriptBtn_clicked();
	void on_resetMachineBtn_clicked();
	void on_outremoveBtn_clicked();//离群点清除
	void on_cloudOpenBtn_clicked();//打开点云文件
	void on_cloudExportBtn_clicked();//输出点云


	void addCombox(QString filename);
	void deleteCombox(int index);
	//void on_save2qglviewerbtn_clicked();//点云预览
	void on_saveCloudBtn_clicked();//保存点云
	

private:
	void timerEvent(QTimerEvent *event);
	void showInViewer(const cv::Mat& depth,glViewer *viewer);
	kfusion::KinFuParams setKinfuParams();//通过面板设置kinfu参数
	void setScanParams(kinectParams &kp);//设置扫描参数
	QString to_QString(string s){return QString::fromLocal8Bit(s.c_str());};//转换string到QString
	int checkGPUdevice();//检查GPU设备
	void setScanToDefault();//重置初始化扫描参数
	void setkinfuToDefault();//重置Kinfu参数
	void setGPUinfo();//设置GPU信息
	QStringList findAvailablePort();//查找全部可用端口
	QString _getCom(int index ,QString keyorvalue);//查找端口
	void init_scriptList();

};

#endif // MAINFORM_H
