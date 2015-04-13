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
	
	Ui::mainFormClass *ui;
	OpenNISource _capture;
	
private slots:
	void on_ConnectKinect_triggered();
	void on_Scan_triggered();

private:
	void init_gpu_device();
	KinFu & init_fusion();
protected:
	void timerEvent(QTimerEvent *event);
	void show_raycasted(KinFu& kinfu);
};

#endif // MAINFORM_H
