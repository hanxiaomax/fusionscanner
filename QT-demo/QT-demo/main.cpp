#include "mainform.h"
#include <QtGui/QApplication>
#include <io/capture.hpp>

using namespace std;


int main(int argc, char *argv[])
{
	int device = 0;
	cuda::setDevice (device);//����GPU��0
	cuda::printShortCudaDeviceInfo (device);//��ӡGPU��Ϣ
	QApplication a(argc, argv);
	mainForm w;
	w.show();
	return a.exec();
}
