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
	: QGLViewer(QGLFormat(QGL::SampleBuffers), parent),kinect_state(false),facility_state(false),GPU_state(false){
		setAttribute(Qt::WA_NoSystemBackground);
}

void InitViewer::updateStates(bool fstate,bool Gstate,bool kstate)
{
	kinect_state=kstate;
	facility_state=fstate;
	GPU_state=Gstate;
	update();
}
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
	const float nbSteps = 200.0;

	glBegin(GL_QUAD_STRIP);
	for (int i=0; i<nbSteps; ++i)
	{
		const float ratio = i/nbSteps;
		const float angle = 21.0*ratio;
		const float c = cos(angle);
		const float s = sin(angle);
		const float r1 = 1.0 - 0.8f*ratio;
		const float r2 = 0.8f - 0.8f*ratio;
		const float alt = ratio - 0.5f;
		const float nor = 0.5f;
		const float up = sqrt(1.0-nor*nor);
		glColor3f(1.0-ratio, 0.2f , ratio);
		glNormal3f(nor*c, up, nor*s);
		glVertex3f(r1*c, alt, r1*s);
		glVertex3f(r2*c, alt+0.05f, r2*s);
	}
	glEnd();
}

void InitViewer::init()
{
	restoreStateFromFile();
	//setBackgroundColor(QColor(245,222,179, 100));
}

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

QString InitViewer::helpString() const
{
	QString text("<h2>O v e r p a i n t</h2>");
	text += "This example shows how to mix the 2D QPainter drawing with regular 3D in an OpenGL QGLViewer.<br>";
	text += "The <code>paintEvent</code> method is overloaded to interleave the two drawing codes.";
	return text;
}
