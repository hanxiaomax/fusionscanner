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
/*主窗口*/


class mainform : public QMainWindow
{
	Q_OBJECT

public:
	mainform(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainform();

private:
	Ui::mainformClass *ui;//初始化ui对象
	fusionScanner*  _scanner;
	OpenNISource* _capture;
	int viewerTimer;
	int updateTimer;
	cv::Mat frame;

private slots:
	void on_connectKinect_triggered();
	void on_connectlifter_triggered();
private:
	void timerEvent(QTimerEvent *event);
};

#endif // MAINFORM_H
