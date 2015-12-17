#include "MeshViewer.h"
#include <iostream>
#include <QKeyEvent>
#include <pcl/features/normal_3d_omp.h>
using namespace qglviewer;
using namespace std;
MeshViewer::MeshViewer(QWidget *parent): 
	QGLViewer(parent),
	cloud(new pcl::PointCloud<pcl::PointNormal>()),
	wireframe_(false)
{


};

void MeshViewer::draw()
{
	if (input_mesh.polygons.size()>0)
	{
		
		for(std::vector< ::pcl::Vertices>::iterator tri=input_mesh.polygons.begin();tri!=input_mesh.polygons.end();tri++)
		{
			pcl::PointNormal p1,p2,p3;
			p1=cloud->points[(*tri).vertices[0]];
			p2=cloud->points[(*tri).vertices[1]];
			p3=cloud->points[(*tri).vertices[2]];
			glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(p1.normal_x,p1.normal_y,p1.normal_z);
			//glMaterialfv()
			glVertex3f(p1.x,p1.y,p1.z);
			glNormal3f(p2.normal_x,p2.normal_y,p2.normal_z);
			glVertex3f(p2.x,p2.y,p2.z);
			glNormal3f(p3.normal_x,p3.normal_y,p3.normal_z);
			glVertex3f(p3.x,p3.y,p3.z);
			glEnd();
		}
	}
	else
	{
		/*glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		qglColor(QColor(255,255,255));
		QFont font("Microsoft YaHei",25,20);

		drawText(width()/2-140,height()/2,tr("没有可显示的Mesh"),font);
		glPopMatrix();*/
	}
}

void MeshViewer::init()
{
	float pos[3] = {1.0, 1.0,1.0};
	const GLfloat light_ambient[4]  = {0.0f, 0.0f, 0.0f, 1.0};
	const GLfloat light_diffuse[4]  = {1.0, 1.0f, 1.0f, 1.0};
	const GLfloat light_specular[4] = {1.0, 1.0f, 1.0f, 1.0};

	glEnable ( GL_LIGHTING ) ;
	glEnable(GL_LIGHT0);
	
	glLightfv(GL_LIGHT0, GL_POSITION, pos);//设置light_0的位置为(1,1,0)
	//Set GL_LIGHT_0's Ambient color to 0,0,0,1
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);//环境强度
	//Set GL_LIGHT_0's Specular color to 1,1,1,1
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//镜面强度
	//Set GL_LIGHT_0's Diffuse color to 1,1,1,1
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);//散射强度
	
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
	glEnable ( GL_COLOR_MATERIAL ) ;//颜色驱动
	glShadeModel(GL_SMOOTH);
	restoreStateFromFile();
	
	
}


void MeshViewer::setMeshBuffer(pcl::PolygonMesh &input)
{
	input_mesh=input;
	pcl::fromPCLPointCloud2<pcl::PointNormal>(input_mesh.cloud,*cloud);
	//pcl::PLYWriter w;
	//w.write("./mesh_cloud.ply",*cloud);
	cout<<"done"<<endl;
}

void MeshViewer::keyPressEvent(QKeyEvent *e)
{
	if (e->key()==Qt::Key_W)
	{
		wireframe_ = !wireframe_;
		if (wireframe_)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		updateGL();
	}
	else
		QGLViewer::keyPressEvent(e);
}