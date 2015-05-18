#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include "ui_mainform.h"
#include <io/capture.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <kfusion/kinfu.hpp>
#include <io/capture.hpp>
#include <kfusion/CloudIO.h>
#include <fstream>
#include "fusionScanner.h"
#include <QTimer>
/*������*/


class mainform : public QMainWindow
{
	Q_OBJECT

public:
	mainform(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainform();

private:
	Ui::mainformClass ui;//�����ڲ�ʹ�ã���ʱ�Ѿ������˶���ui������˳�ʼ������Ҫ���캯��֧�֣�
	fusionScanner*  _scanner;//��һ�����õ����Ҳ��ǲ���������Ϊָ��
	OpenNISource* _capture;//��һ�����õ����Ҳ��ǲ���������Ϊָ��
	int updateTimer;
	int delayTimer;
	//QTimer *delayTimer;//һ�����õ����Ҳ��ǲ�����Ӧ������Ϊ���󣬵���QTimer������һ��private���͵Ŀ������캯������ֹ�Դ�ֵ�ķ�ʽʹ�ã�ͬʱҲ��ֹ��ֵ��ʼ������TIC P.518��

	cv::Mat frame;

private slots:
	void on_connectKinect_triggered();//����kinect�豸�����gpu
	void on_ToolstartBtn_triggered();//����ɨ��
	void on_ToolstopBtn_triggered();//ֹͣɨ��
	void on_TooldeleteBtn_triggered();//�����λ
	void on_actionSaveCloud_triggered();//�������


	void resetToDefault();//���ó�ʼ��ɨ�����
	void onShowCloudBtn();
private:
	void timerEvent(QTimerEvent *event);
	void showInViewer(const cv::Mat& depth,glViewer *viewer);
	
};

#endif // MAINFORM_H
