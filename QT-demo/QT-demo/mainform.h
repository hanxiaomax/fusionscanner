#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include "ui_mainform.h"
#include <opencv2/core/core.hpp>
#include <kfusion/kinfu.hpp>
#include <io/capture.hpp>
using namespace kfusion;

class mainForm : public QMainWindow
{
	Q_OBJECT

public:
	mainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainForm();
	
private:
	
	OpenNISource _capture;
	KinFu::Ptr kinfu_;
	cv::Mat view_host_;
	Ui::mainFormClass *ui;
	cuda::Image view_device_;
	cuda::Depth depth_device_;
	cuda::DeviceArray<Point> cloud_buffer;
	

private slots:
	void on_actionKinect_triggered();

protected:
	void timerEvent(QTimerEvent *event);
	void show_raycasted(KinFu& kinfu);
};

#endif // MAINFORM_H
