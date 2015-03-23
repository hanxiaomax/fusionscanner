#include "mainform.h"
#include <QtGui/QApplication>

#ifndef ANIMAL_H_H  
#define ANIMAL_H_H  
	#include <App.h>
#endif ANIMAL_H_H  

using namespace std;
using namespace kfusion;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	mainForm w;
	w.show();

	return a.exec();
}
