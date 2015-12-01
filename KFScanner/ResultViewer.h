#ifndef RESULTVIEWER_H
#define RESULTVIEWER_H
#include <QGLViewer/qglviewer.h>
#include <QTextCodec> 
#include <kfusion/types.hpp>
#include "QGLViewer/frame.h"

//点云frame
class _PointFrame
{
public :
	void draw() const;
	qglviewer::Frame frame;
};

using namespace kfusion;

/////////////////////////////////////////////////////////////
class QPaintEvent;
class QPainter;
class ResultViewer : public QGLViewer
{
	Q_OBJECT

public:
	ResultViewer(QWidget *parent);
	//void update(){cout<<"update"<<endl;updateGL();};//update是QWidget实现的
	void setPcdBuffer(vertexes &pcd);//设置可视化点云
	vertexes & getPcdBuffer(){return pcd_buffer;};
	void setInputCloud(pcl::PointCloud<pcl::PointNormal> &input){input_cloud=input;};//设置输入点云

public slots:
    bool remove_point();//移除选中点
signals: 
	void delete_pressed();

protected :
  virtual void draw();
  virtual void init();
  virtual void drawWithNames();
  virtual void endSelection(const QPoint&);
  virtual void mousePressEvent(QMouseEvent *e);
  virtual void mouseMoveEvent(QMouseEvent *e);
  virtual void mouseReleaseEvent(QMouseEvent *e);
  virtual void keyPressEvent(QKeyEvent *e);
  virtual void paintEvent(QPaintEvent *event);
 
private:
	vertexes pcd_buffer;
	pcl::PointCloud<pcl::PointNormal> input_cloud;
	pcl::PointIndices::Ptr remove_indice;
	QRect rectangle_;//矩形选择框
	enum SelectionMode { NONE, ADD, REMOVE };//模式
	SelectionMode selectionMode_;
	QList<_PointFrame*> objects_;//所有点的集合
	QList<int> selection_;//所有选中元素的集合
	string infoText;
	int showtime;
private:
	void timerEvent(QTimerEvent *event);
	void drawSelectionRectangle() const;//绘制选择框
	void addIdToSelection(int id);//添加选中元素到列表
	void removeIdFromSelection(int id);//从列表中移除选中元素
	void reset();//复位选择状态
	void drawLegend(QPainter *painter);//绘制图例
};





#endif // RESULTVIEWER_H
