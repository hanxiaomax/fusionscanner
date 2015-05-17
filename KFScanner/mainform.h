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
/*主窗口*/


class mainform : public QMainWindow
{
	Q_OBJECT

public:
	mainform(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainform();

private:
	Ui::mainformClass ui;//一定会用到，且不是参数，声明为对象
	fusionScanner*  _scanner;//不一定会用到，且不是参数，声明为指针
	OpenNISource* _capture;//不一定会用到，且不是参数，声明为指针
	int viewerTimer;
	int updateTimer;
	QTimer *delayTimer;//一定会用到，且不是参数，应该声明为对象，但是QTimer声明了一个private类型的拷贝构造函数，防止以传值的方式使用，同时也阻止了值初始化。《TIC P.518》
	cv::Mat frame;

private slots:
	void on_connectKinect_triggered();
	void on_ToolstartBtn_triggered();
	void on_ToolstopBtn_triggered();
	void on_TooldeleteBtn_triggered();
	void resetToDefault();
private:
	void timerEvent(QTimerEvent *event);
	void showInViewer(const cv::Mat& depth,glViewer *viewer);
};

#endif // MAINFORM_H
