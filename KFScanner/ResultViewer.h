#ifndef RESULTVIEWER_H
#define RESULTVIEWER_H
#include <QGLViewer/qglviewer.h>
#include <QTextCodec> 
#include <kfusion/types.hpp>
#include "QGLViewer/frame.h"

//����frame
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
	//void update(){cout<<"update"<<endl;updateGL();};//update��QWidgetʵ�ֵ�
	void setPcdBuffer(vertexes &pcd);//���ÿ��ӻ�����
	vertexes & getPcdBuffer(){return pcd_buffer;};
	void setInputCloud(pcl::PointCloud<pcl::PointNormal>::Ptr input){input_cloud=input;};//�����������
	//pcl::PointCloud<pcl::PointNormal> getInputCloud(){return input_cloud;};


public slots:
    bool remove_point();//�Ƴ�ѡ�е�
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
	pcl::PointCloud<pcl::PointNormal>::Ptr input_cloud;
	pcl::PointIndices::Ptr remove_indice;
	QRect rectangle_;//����ѡ���
	enum SelectionMode { NONE, ADD, REMOVE };//ģʽ
	SelectionMode selectionMode_;
	QList<_PointFrame*> objects_;//���е�ļ���
	QList<int> selection_;//����ѡ��Ԫ�صļ���
	string infoText;
	int showtime;
private:
	void timerEvent(QTimerEvent *event);
	void drawSelectionRectangle() const;//����ѡ���
	void addIdToSelection(int id);//���ѡ��Ԫ�ص��б�
	void removeIdFromSelection(int id);//���б����Ƴ�ѡ��Ԫ��
	void reset();//��λѡ��״̬
	void drawLegend(QPainter *painter);//����ͼ��
};





#endif // RESULTVIEWER_H
