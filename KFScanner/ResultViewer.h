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
	void setPcdBuffer(pcl::PointCloud<pcl::PointNormal>::Ptr pcd);
	pcl::PointCloud<pcl::PointNormal>::Ptr getPcdBuffer(){return pcd_buffer_;};
	void setInputCloud(pcl::PointCloud<pcl::PointNormal>::Ptr input){input_cloud=input;};//设置输入点云

	

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
	pcl::PointCloud<pcl::PointNormal>::Ptr pcd_buffer_;
	pcl::PointCloud<pcl::PointNormal>::Ptr input_cloud;
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
