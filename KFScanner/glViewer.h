#pragma once
#ifndef GLVIEWER_H
#define GLVIEWER_H
#include <QtOpenGL/QGLWidget>
#include <opencv2/core/core.hpp>
class glViewer :public QGLWidget
{
public:
	explicit glViewer(QWidget *parent = 0);
	~glViewer(void);
};

#endif