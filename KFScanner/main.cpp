#include "mainform.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	mainform w;
	w.show();
	return app.exec();
}
