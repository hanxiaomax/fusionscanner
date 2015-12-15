#ifndef CLOUDVIEWER_H
#define CLOUDVIEWER_H

#include <QGLViewer/qglviewer.h>
#include <kfusion\types.hpp>
using namespace kfusion;

class CloudViewer : public QGLViewer
{

public:
	CloudViewer::CloudViewer(QWidget *parent): QGLViewer(parent),vizScale(1.0f),pcd_buffer_(new pcl::PointCloud<pcl::PointNormal>()){};

protected:
	virtual void draw();
	virtual void init();
public:

	void setPcdBuffer(pcl::PointCloud<pcl::PointNormal>::Ptr pcd){pcd_buffer_=pcd;};
	pcl::PointCloud<pcl::PointNormal> getPcdBuffer(){return *pcd_buffer_;};
private:
	pcl::PointCloud<pcl::PointNormal>::Ptr pcd_buffer_;
	float vizScale;


};


#endif