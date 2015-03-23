#include "mainform.h"
#include "ui_mainform.h"
mainForm::mainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),ui(new Ui::mainFormClass)
{
	ui->setupUi(this);
}

mainForm::~mainForm()
{
	
}

void mainForm::on_actionCam_triggered()
{
	if( !mCapture.isOpened() )
		if( !mCapture.open( 0 ) )
			return;

	startTimer(0);
}


void mainForm::timerEvent(QTimerEvent *event)
{
	cv::Mat image;
	mCapture >> image;

	// Do what you want with the image :-)

	// Show the image
	ui->widget->showImage( image );
}
