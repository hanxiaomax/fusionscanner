#include "mainform.h"
#include <QtGui/QApplication>
#include <io/capture.hpp>

using namespace std;


int main(int argc, char *argv[])
{
	int device = 0;
	cuda::setDevice (device);//设置GPU：0
	cuda::printShortCudaDeviceInfo (device);//打印GPU信息
	QApplication a(argc, argv);
	mainForm w;
	w.show();
	return a.exec();
}
