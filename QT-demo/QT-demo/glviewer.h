#pragma once
#ifndef GLVIEWER_H
#define GLVIEWER_H
#include <QtOpenGL/QGLWidget>
#include <opencv2/core/core.hpp>

/*我们promote了一个新的控件，因此要为其单独创建一个类，包括一个h文件和cpp文件*/
class glviewer :public QGLWidget
{
	 Q_OBJECT//所以带有信号槽的类都需要声明
public:
	explicit glviewer(QWidget *parent = 0);//防止编译器优化单参数构造函数
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
