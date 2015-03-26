#include "mainform.h"
#include "ui_mainform.h"
#include <io/capture.hpp>


mainForm::mainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),ui(new Ui::mainFormClass)
{
	ui->setupUi(this);
}

mainForm::~mainForm()
{
}

void mainForm::on_actionKinect_triggered()
{
	_capture.open(0);

	startTimer(0);
}


void mainForm::timerEvent(QTimerEvent *event)
{
	cv::Mat depth, image;

	// Do what you want with the image :-)

	// Show the image
	_capture.grab(depth, image);
	ui->Dviewer->showImage( depth );
	ui->GRBviewer->showImage(image);
}
