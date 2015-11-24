#ifndef RESULTVIEWER_H
#define RESULTVIEWER_H
#include <QGLViewer/qglviewer.h>
#include <QTextCodec> 
#include <kfusion\types.hpp>
using namespace kfusion;



class ResultViewer : public QGLViewer
{
	Q_OBJECT

public:
	ResultViewer(QWidget *parent){QTextCodec::setCodecForTr(QTextCodec::codecForLocale());};
	void update();
	void setPcdBuffer(vertexes &pcd){pcd_buffer=pcd;};
	vertexes & getPcdBuffer(){return pcd_buffer;};
public slots:
    //void open();//移到主面板

protected :
  virtual void draw();
  virtual void init();
  virtual void mousePressEvent(QMouseEvent* e);//右键显示选中点的个数，删除操作等

private:
	vertexes pcd_buffer;
	float vizScale;
};

#endif // RESULTVIEWER_H
