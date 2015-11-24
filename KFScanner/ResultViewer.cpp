#include "ResultViewer.h"


#include <QFileDialog>
#include <QMenu>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMap>
#include <QCursor>
#include <QtGui/QApplication>
#include <math.h>
#include <iostream>
#include <kfusion/CloudIO.h>


using namespace std;


void ResultViewer::update()
{
	updateGL();
}
void ResultViewer::draw()
{ 
	glPushMatrix();
	glScaled(vizScale,vizScale,vizScale);//���ű���
	glDisable(GL_LIGHTING);
	//glPointSize(5.0f);
	
	glColor3f(1,1,0);
	glBegin(GL_POINTS);
	for (int i = 0; i < pcd_buffer.size(); ++i) 
	{
		glVertex3d(pcd_buffer[i].x,pcd_buffer[i].y,pcd_buffer[i].z);//����һ����
	}
	glEnd();
	glPopMatrix();
}

void ResultViewer::init()
{
	restoreStateFromFile();

    setFPSIsDisplayed();

	setSceneBoundingBox(qglviewer::Vec(-50,-50,-50), qglviewer::Vec(50,50,50));

	showEntireScene();
	vizScale=80.0f;
	
}


/*----------------------------------------*
 *  ���°�����¼�
 ----------------------------------------*/ 
void ResultViewer::mousePressEvent(QMouseEvent* e)
{
  if ((e->button() == Qt::RightButton) && (e->modifiers() == Qt::NoButton))//���һ��¼�
	{
	  QMenu menu( this );
	  QMenu *menu_pos;
	  menu.addAction("PointCloud Viewer");
	  menu.addSeparator();
	  QMap<QAction*, int> menuMap;

	  QAction *open_action= new QAction(tr("Open Point Cloud"),this) ;

	  //connect(open_action,SIGNAL(triggered()),this,SLOT(open()));


	  menu.addAction(open_action);//�򿪰�ť
	  menu_pos=menu.addMenu("Positon");//�����˵���Ԥ����λ��

	  bool atLeastOne = false;
	  for (unsigned short i=0; i<20; ++i)
		if (camera()->keyFrameInterpolator(i))
	  {
		atLeastOne = true;
		QString text;
		if (camera()->keyFrameInterpolator(i)->numberOfKeyFrames() == 1)
		  text = "Position "+QString::number(i);
		else
		  text = "Path "+QString::number(i);

		menuMap[menu_pos->addAction(text)] = i;
	  }

	  if (!atLeastOne)
	  {
		  menu_pos->addAction("No pre-defined positions");
		  menu_pos->addAction("Use to Alt+Fx to define one");
	  }

	  QAction* action = menu.exec(e->globalPos());

	  if (atLeastOne && action)
		  camera()->playPath(menuMap[action]);
	}

  else if(e->buttons() ==Qt::MidButton)
  {

	  cout<<"2"<<endl;
  }
  else
	QGLViewer::mousePressEvent(e);
}

//void ResultViewer::open()
//{
//	
//	pcd_buffer.clear();//��յ���buffer���������ֵ���
//	QString filename = QFileDialog::getOpenFileName(this,tr("open point cloud"),".",tr("*.ply"));
//	if(!filename.isEmpty())
//	{	
//		PLYFilereader reader;
//		reader.readToVertexes(filename.toStdString(),pcd_buffer,false);//�����Լ���pcd_buffer,����Ӱ��������
//		cout<<"open: "<<filename.toStdString()<<endl;
//
//	}
//	updateGL();
//}

