#pragma once
#ifndef GLVIEWER_H
#define GLVIEWER_H
#include <QtOpenGL/QGLWidget>
#include <opencv2/core/core.hpp>


class glviewer :public QGLWidget
{
	 Q_OBJECT
public:
	explicit glviewer(QWidget *parent = 0);
	~glviewer(void);
signals:
	void    imageSizeChanged( int outW, int outH );
public slots:
	bool    showImage( cv::Mat image ); /// Used to set the image to be viewed
protected:
	void 	initializeGL(); /// OpenGL initialization
	void 	paintGL(); /// OpenGL Rendering
	void 	resizeGL(int width, int height);        /// Widget Resize Event

	void        updateScene();
	void        renderImage();

private:
	bool        mSceneChanged;          /// Indicates when OpenGL view is to be redrawn

	QImage      mRenderQtImg;           /// Qt image to be rendered
	cv::Mat     mOrigImage;             /// original OpenCV image to be shown

	QColor      mBgColor;		/// Background color

	int         mOutH;                  /// Resized Image height
	int         mOutW;                  /// Resized Image width
	float       mImgRatio;             /// height/width ratio

	int         mPosX;                  /// Top left X position to render image in the center of widget
	int         mPosY;                  /// Top left Y position to render image in the center of widget
};


#endif 
