#ifndef CLOUDVIEWER_H
#define CLOUDVIEWER_H

#include <QGLViewer/qglviewer.h>
#include <kfusion\types.hpp>
using namespace kfusion;

class CloudViewer : public QGLViewer
{

public:
	CloudViewer::CloudViewer(QWidget *parent): QGLViewer(parent),vizScale(1.0f){};

protected:
	virtual void draw();
	virtual void init();
public:
	void update(vertexes v);
private:
	vertexes pcd_buffer;
	float vizScale;
};


#endif