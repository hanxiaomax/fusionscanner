#include "mainform.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	int device = 0;
	cuda::setDevice (device);//����GPU��0
	cuda::printShortCudaDeviceInfo (device);//��ӡGPU��Ϣ



	QApplication a(argc, argv);
	mainform w;
	w.show();
	return a.exec();
}
