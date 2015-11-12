#ifndef INITVIEWER_H
#define INITVIEWER_H

#include <QGLViewer/qglviewer.h>

class InitViewer : public QGLViewer
{
	Q_OBJECT

public:
	InitViewer(QWidget *parent):QGLViewer(parent),wireframe_(false), flatShading_(false){};

protected :
  virtual void draw();
  virtual void init();
  virtual void keyPressEvent(QKeyEvent *e);
  virtual void mousePressEvent(QMouseEvent* e);

private :
  bool wireframe_, flatShading_;
	
};

#endif // INITVIEWER_H
