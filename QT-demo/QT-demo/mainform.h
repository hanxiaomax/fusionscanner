#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include "ui_mainform.h"
#include <App.h>


class mainForm : public QMainWindow
{
	Q_OBJECT

public:
	mainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainForm();

private:
	Ui::mainFormClass *ui;
	cv::VideoCapture mCapture;

private slots:
	void on_actionCam_triggered();
protected:
	void timerEvent(QTimerEvent *event);
};

#endif // MAINFORM_H
