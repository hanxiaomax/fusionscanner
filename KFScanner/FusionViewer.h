#ifndef FUSIONVIEWER_H
#define FUSIONVIEWER_H

#include <QGLViewer/qglviewer.h>

class FusionViewer : public QGLViewer
{
	Q_OBJECT

public:
	FusionViewer(QWidget *parent):QGLViewer(parent){};

protected:
	virtual void draw(){};
	virtual void init(){};
public:
	void update(){};

};

#endif // FUSIONVIEWER_H
