#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include "ui_mainform.h"
#include <io/capture.hpp>

/*������*/
class mainform : public QMainWindow
{
	Q_OBJECT

public:
	mainform(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainform();

private:
	Ui::mainformClass ui;//��ʼ��ui����

private slots:
	void on_connectKinect_triggered();
	void on_connectlifter_triggered();


};

#endif // MAINFORM_H
