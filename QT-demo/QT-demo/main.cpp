#include "mainform.h"
#include <QtGui/QApplication>
#include <io/capture.hpp>

using namespace std;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	mainForm w;
	w.show();
	return a.exec();
}
