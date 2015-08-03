#ifndef MAINFORM_H
#define MAINFORM_H
#include <QtGui/QMainWindow>
#include "ui_mainform.h"
#include "script_management.h"
#include <io/capture.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <kfusion/kinfu.hpp>
#include <io/capture.hpp>
#include <kfusion/CloudIO.h>
#include <iostream>
#include <fstream>
#include "fusionScanner.h"
#include <QTimer>
#include "3rdparty/qextserialport/qextserialport.h"//���������ڿ�

class mainform : public QMainWindow
{
	Q_OBJECT

public:
	mainform(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainform();

private:
	Ui::mainformClass ui;//�����ڲ�ʹ�ã���ʱ�Ѿ������˶���ui������˳�ʼ������Ҫ���캯��֧�֣�
	script_Dialog * sd;
	fusionScanner*  _scanner;//��һ�����õ����Ҳ��ǲ���������Ϊָ��
	OpenNISource* _capture;//��һ�����õ����Ҳ��ǲ���������Ϊָ��
	QextSerialPort * port;
	int updateTimer;
	int delayTimer;
	//QTimer *delayTimer;//һ�����õ����Ҳ��ǲ�����Ӧ������Ϊ���󣬵���QTimer������һ��private���͵Ŀ������캯������ֹ�Դ�ֵ�ķ�ʽʹ�ã�ͬʱҲ��ֹ��ֵ��ʼ������TIC P.518��
	QTimer *Serital_Timer;
	QStringList m_listCommand;  //�����͵�����
	wchar_t subkey[80];
	wchar_t keyname[256]; //��������
	char keyvalue[256];  //��ֵ����
	int indexnum;
	DWORD keysize,type,valuesize;
	HKEY hKey;
	bool isOpen;
	cv::Mat frame;
	

private slots:
	void on_connectKinect_triggered();//����kinect�豸�����gpu
	void on_ToolstartBtn_triggered();//����ɨ��
	void on_ToolstopBtn_triggered();//ֹͣɨ��
	void on_TooldeleteBtn_triggered();//�����λ
	void on_actionSaveCloud_triggered();//�������
	void on_action_ResetKinFuParams_triggered();//����kinfu����
	void on_action_ResetScanParams_triggered();//����ɨ�����
	void on_scanPortBtn_clicked();
	void on_connectPortBtn_clicked();
	void on_newScriptBtn_clicked();
	void on_resetMachineBtn_clicked();
	void on_outremoveBtn_clicked();
	void addCombox(QString filename);
	void deleteCombox(int index);
	
private:
	void timerEvent(QTimerEvent *event);
	void showInViewer(const cv::Mat& depth,glViewer *viewer);
	kfusion::KinFuParams setKinfuParams();//ͨ���������kinfu����
	void setScanParams(kinectParams &kp);//����ɨ�����
	QString to_QString(string s){return QString::fromLocal8Bit(s.c_str());};//ת��string��QString
	int checkGPUdevice();//���GPU�豸
	void setScanToDefault();//���ó�ʼ��ɨ�����
	void setkinfuToDefault();//����Kinfu����
	void setGPUinfo();//����GPU��Ϣ
	QStringList findAvailablePort();//����ȫ�����ö˿�
	QString _getCom(int index ,QString keyorvalue);//���Ҷ˿�
	void init_scriptList();
};

#endif // MAINFORM_H
