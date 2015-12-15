#include "ResultViewer.h"
#include <QFileDialog>
#include <QMenu>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMap>
#include <QCursor>
#include <QtGui/QApplication>
#include <QMessageBox>
#include <QPainter>
#include <QTextDocument>
#include <kfusion/CloudIO.h>
#include "pcl/extract_indices.h"

#include <math.h>
#include <iostream>

using namespace std;

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif



ResultViewer::ResultViewer(QWidget *parent):
	selectionMode_(NONE),
	remove_indice(new pcl::PointIndices()),
	input_cloud(new pcl::PointCloud<pcl::PointNormal>())
{
	setAttribute(Qt::WA_NoSystemBackground);
	setTextIsEnabled();
}

void ResultViewer::init()
{
	restoreStateFromFile();

	setSceneBoundingBox(qglviewer::Vec(-0.5f,-0.5f,-0.5f), qglviewer::Vec(0.5f,0.5f,0.5f));//设置场景的尺寸（min,max）
	showEntireScene();//显示全景

	glBlendFunc(GL_ONE, GL_ONE);

	setSelectBufferSize(40000);//一次最多能够选择10k个对象

}


void ResultViewer::draw()
{ 
	glDisable(GL_LIGHTING);//否则看不到点
	//绘制全部被选择的点
	glColor3f(1, 0.3f, 0.3f);
	for (QList<int>::const_iterator it=selection_.begin(), end=selection_.end(); it != end; ++it)
		objects_.at(*it)->draw();
	//绘制全部的点，已绘制的不重绘
	glColor3f(1.0f,1.0f,0);
	for (int i=0; i<int(objects_.size()); i++)
		objects_.at(i)->draw();

	if (selectionMode_ != NONE)
		drawSelectionRectangle();//绘制选择框
}



void ResultViewer::drawWithNames()
{
	for (int i=0; i<int(objects_.size()); i++)
	{
		glPushName(i);
		objects_.at(i)->draw();
		glPopName();
	}
}

void ResultViewer::endSelection(const QPoint&)
{
	// Flush GL buffers
	glFlush();

	// Get the number of objects that were seen through the pick matrix frustum. Reset GL_RENDER mode.
	GLint nbHits = glRenderMode(GL_RENDER);

	if (nbHits > 0)
	{
		// Interpret results : each object created 4 values in the selectBuffer().
		// (selectBuffer())[4*i+3] is the id pushed on the stack.
		for (int i=0; i<nbHits; ++i)
			switch (selectionMode_)
		{
			case ADD    : addIdToSelection((selectBuffer())[4*i+3]); break;
			case REMOVE : removeIdFromSelection((selectBuffer())[4*i+3]);  break;
			default : break;
		}
	}

	for (QList<int>::Iterator it=selection_.begin();it!=selection_.end();it++)//把选中object的id加入indice列表
		(*remove_indice).indices.push_back(*it);
	selectionMode_ = NONE;
	infoText="使用Delete按键删除选择点云";
	update();
}
/*----------------------------------------*
 *  重新绑定按键事件
 ----------------------------------------*/
void ResultViewer::keyPressEvent(QKeyEvent *e)
{
	//添加自定义的按键C
	if (e->key()==Qt::Key_Delete)
	{
		if(input_cloud->size()>0)
		{
			if(remove_point())
				update();
			else
				QMessageBox::information(NULL, tr("警告"), tr("失败"));
		}
		else
			QMessageBox::information(NULL, tr("警告"), tr("没有可以用来处理的点云"));
	}
	else
		QGLViewer::keyPressEvent(e);

}

/*----------------------------------------*
 *  重新绑定鼠标事件
 ----------------------------------------*/ 
void ResultViewer::mousePressEvent(QMouseEvent* e)
{
	// Start selection. Mode is ADD with Shift key and TOGGLE with Alt key.
	rectangle_ = QRect(e->pos(), e->pos());

	if ((e->button() == Qt::LeftButton) && (e->modifiers() == Qt::ShiftModifier))
		selectionMode_ = ADD;
	else
		if ((e->button() == Qt::LeftButton) && (e->modifiers() == Qt::AltModifier))
			selectionMode_ = REMOVE;
		else
			QGLViewer::mousePressEvent(e);
		
}

void ResultViewer::mouseMoveEvent(QMouseEvent* e)
{
	if (selectionMode_ != NONE)
	{
		// Updates rectangle_ coordinates and redraws rectangle
		rectangle_.setBottomRight(e->pos());
		update();
	}
	else
		QGLViewer::mouseMoveEvent(e);
}

void ResultViewer::mouseReleaseEvent(QMouseEvent* e)
{
	if (selectionMode_ != NONE)
	{
		rectangle_ = rectangle_.normalized();
		setSelectRegionWidth(rectangle_.width());
		setSelectRegionHeight(rectangle_.height());
		select(rectangle_.center());
		update();

	}
	else
		QGLViewer::mouseReleaseEvent(e);
	
}
/*----------------------------------------*
 *  功能描述: 设置待显示的点云
 ----------------------------------------*/ 

void ResultViewer::setPcdBuffer(pcl::PointCloud<pcl::PointNormal>::Ptr pcd)
{
	pcd_buffer_=pcd;
	reset();//复位selection，objects和remove_indices

	for (int i = 0; i < pcd_buffer_->size(); ++i) 
	{
		_PointFrame * p = new _PointFrame();
		
		p->frame.setPosition(qglviewer::Vec(pcd_buffer_->points[i].x,pcd_buffer_->points[i].y,pcd_buffer_->points[i].z));
		objects_.append(p);		
	}
 }

/*----------------------------------------*
 *  功能描述: 矩形选择框
 ----------------------------------------*/ 
void ResultViewer::drawSelectionRectangle() const
{
	startScreenCoordinatesSystem();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);

	glColor4f(0.0, 0.4f, 0.3f, 0.3f);
	glBegin(GL_QUADS);
	glVertex2i(rectangle_.left(),  rectangle_.top());
	glVertex2i(rectangle_.right(), rectangle_.top());
	glVertex2i(rectangle_.right(), rectangle_.bottom());
	glVertex2i(rectangle_.left(),  rectangle_.bottom());
	glEnd();

	glLineWidth(2.0);
	glColor4f(0.4f, 0.4f, 0.5f, 0.5f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(rectangle_.left(),  rectangle_.top());
	glVertex2i(rectangle_.right(), rectangle_.top());
	glVertex2i(rectangle_.right(), rectangle_.bottom());
	glVertex2i(rectangle_.left(),  rectangle_.bottom());
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	stopScreenCoordinatesSystem();
}

/*----------------------------------------*
 *  功能描述: 添加被选中的元素
 ----------------------------------------*/ 
void ResultViewer::addIdToSelection(int id)
{
	if (!selection_.contains(id))
		selection_.push_back(id);
}
/*----------------------------------------*
 *  功能描述: 移除被选中的元素
 ----------------------------------------*/ 
void ResultViewer::removeIdFromSelection(int id)
{
	selection_.removeAll(id);
}
/*----------------------------------------*
 *  功能描述: 从点云中移除选中点
 ----------------------------------------*/ 
bool ResultViewer::remove_point()
{
	try
	{
		pcl::PCLPointCloud2::Ptr input_temp(new pcl::PCLPointCloud2()),//临时输入
								output_temp(new pcl::PCLPointCloud2());//输出为PCLPointCloud2
		pcl::PointCloud<pcl::PointNormal> output_cloud;//输出点云
		pcl::PointCloud<pcl::PointNormal> new_pcd;

		pcl::toPCLPointCloud2<pcl::PointNormal>(*input_cloud,*input_temp);//转换为ExtractIndices可用的PCLPointCloud2格式temp
		pcl::ExtractIndices<pcl::PCLPointCloud2> extract;
		extract.setInputCloud(input_temp);
		extract.setIndices(remove_indice);
		extract.setNegative(true);
		extract.filter(*output_temp);
	

		pcl::fromPCLPointCloud2<pcl::PointNormal>(*output_temp,output_cloud);
		
		
		*input_cloud=output_cloud;//以输出点云更新输入点云
		setPcdBuffer(input_cloud);
		
		return true;
	}
	catch (...)
	{
		return false;
	}
}

void ResultViewer::reset()
{
	selection_.clear();
	objects_.clear();
	remove_indice->indices.clear();
}

void ResultViewer::paintEvent(QPaintEvent *event)//系统调用
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
	qglClearColor(backgroundColor());
	painter.end();
}
void ResultViewer::drawLegend(QPainter *painter)
{
	painter->save();
	const int margin=11;
	const int padding=5;
	QTextDocument textDocument;
	textDocument.setDefaultStyleSheet("*{color:#FFEFEF}");
	QString legend;
	legend="<h4 >点云大小："+QString::number(objects_.size())+"<h4 >选中点个数："+QString::number(selection_.size());
	QString qstr=(tr(legend.toStdString().c_str()));


	textDocument.setHtml(qstr);
	textDocument.setTextWidth(textDocument.size().width());
	

	QRect rect(QPoint(5,5),textDocument.size().toSize()+QSize(2*padding,2*padding));	
	painter->setPen(QColor(255,239,0,31));
	painter->setBrush(QColor(255,0,0,31));
	painter->drawRect(rect);
	painter->translate(padding,padding);
	textDocument.drawContents(painter);
	painter->restore();


	if (infoText.size()>0)
	{
		painter->save();
		QTextDocument infor_text;
		infor_text.setDefaultStyleSheet("*{color:#FF0000;font-size:20px}");
		infor_text.setDefaultFont(QFont("Microsoft Yahei"));
		infor_text.setHtml(tr(infoText.c_str()));
		infor_text.setTextWidth(infor_text.size().width());
		QRect rect_info(QPoint(5,560),infor_text.size().toSize()+QSize(2*padding,2*padding));
		//QRect rect_info(rectangle_.center(),infor_text.size().toSize()+QSize(2*padding,2*padding));
		
		painter->setPen(QColor(255,239,0,31));
		painter->setBrush(QColor(153,255,255,255));
		painter->drawRect(rect_info);
		painter->translate(5,560);
		infor_text.drawContents(painter);
		painter->restore();
		showtime=startTimer(2000);
	}	
}

void ResultViewer::timerEvent(QTimerEvent *e)
{

	if(e->timerId()==showtime)
	{	
		infoText.clear();
		update();
	}
}


#include <qgl.h>
using namespace qglviewer;

void _PointFrame::draw() const
{

	glPushMatrix();
	glMultMatrixd(frame.matrix());
	glBegin(GL_POINTS);
	glVertex3f(0,0,0);
	glEnd();
	glPopMatrix();
}