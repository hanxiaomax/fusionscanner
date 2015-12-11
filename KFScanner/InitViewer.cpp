#include "InitViewer.h"

#include <QPainter>
#include <QTextDocument>
#include <iostream>
#include <string>
using namespace std;

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif




InitViewer::InitViewer(QWidget* parent)
	: QGLViewer(QGLFormat(QGL::SampleBuffers), parent),kinect_state(false),facility_state(false),GPU_state(false)
{
		setAttribute(Qt::WA_NoSystemBackground);
}

/*----------------------------------------*
 *  功能描述: 更新状态并更新显示文字
 ----------------------------------------*/ 
void InitViewer::updateStates(bool fstate,bool Gstate,bool kstate)
{
	kinect_state=kstate;
	facility_state=fstate;
	GPU_state=Gstate;
	
	update();
}
/*----------------------------------------*
 *  功能描述: 绘制图示文字
 ----------------------------------------*/ 
void InitViewer::drawLegend(QPainter *painter)
{
	painter->save();
	const int margin=11;
	const int padding=5;
	QTextDocument textDocument;
	textDocument.setDefaultStyleSheet("*{color:#FFEFEF}");
	string html;
	string kinect,facility,gpu;

	kinect_state?kinect="OK</h4>":kinect="disconnect</h4>";
	facility_state?facility="OK</h4>":facility="disconnect</h4>";
	GPU_state?gpu="OK</h4>":gpu="disconnect</h4>";

	
	html="<h4 >平台状状态："+facility+"<h4 >Kinect状态："+kinect+"<h4 >GPU状态："+gpu;
	
	QString qstr=(tr(html.c_str()));
	textDocument.setHtml(qstr);
	textDocument.setTextWidth(textDocument.size().width());
	QRect rect(QPoint(5,5),textDocument.size().toSize()+QSize(2*padding,2*padding));

	painter->setPen(QColor(255,239,0,31));
	painter->setBrush(QColor(255,0,0,31));
	painter->drawRect(rect);
	painter->translate(padding,padding);
	textDocument.drawContents(painter);
	painter->restore();
}
// Draws a spiral
void InitViewer::draw()
{
	
	
}

void InitViewer::init()
{
	restoreStateFromFile();
}

/*----------------------------------------*
 *  功能描述: 重载绘图事件
 ----------------------------------------*/ 
void InitViewer::paintEvent(QPaintEvent *event)//系统调用
{

	Q_UNUSED(event)
		QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);//反走样

	// Save current OpenGL state
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Reset OpenGL parameters
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_MULTISAMPLE);
	static GLfloat lightPosition[4] = { 1.0, 5.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	qglClearColor(backgroundColor());

	// Classical 3D drawing, usually performed by paintGL().
	preDraw();
	draw();
	postDraw();
	// Restore OpenGL state
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	
	drawLegend(&painter);
	painter.end();
	
}
