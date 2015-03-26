#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include "ui_mainform.h"
#include <opencv2/core/core.hpp>
#include <kfusion/kinfu.hpp>
#include <io/capture.hpp>
//using namespace kfusion;

class mainForm : public QMainWindow
{
	Q_OBJECT

public:
	mainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainForm();
	
private:
	
	kfusion::OpenNISource _capture;
	Ui::mainFormClass *ui;
	
private slots:
	void on_actionKinect_triggered();

protected:
	void timerEvent(QTimerEvent *event);
};

#endif // MAINFORM_H
