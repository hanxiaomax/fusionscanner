#pragma once
#include <QGLViewer/qglviewer.h>
#include <kfusion/types.hpp>
#include <QGLViewer/manipulatedFrame.h>
class MeshViewer :public QGLViewer
{
public:
	MeshViewer(QWidget *parent);
	~MeshViewer(void){};
protected:
	virtual void draw();
	virtual void init();
public:
	void setMeshBuffer(pcl::PolygonMesh &input);
private:
	qglviewer::ManipulatedFrame* light1;
	qglviewer::ManipulatedFrame* light2;
	bool wireframe_;
	void keyPressEvent(QKeyEvent *e);
private:
	pcl::PolygonMesh input_mesh;
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud;

};

