#include "MeshViewer.h"
#include <iostream>

using namespace qglviewer;
using namespace std;
MeshViewer::MeshViewer(QWidget *parent): 
	QGLViewer(parent),
	cloud(new pcl::PointCloud<pcl::PointNormal>()),
	normal(new pcl::PointCloud<pcl::PointNormal>())
{


};

	//void MeshViewer::draw()
	//{
	//	float pos[4] = {1.0, 0.5, 1.0, 0.0};
	//	// Directionnal light
	//	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	//	pos[3] = 1.0;
	//	// Spot light
	//	Vec pos1 = light1->position();
	//	pos[0] = float(pos1.x);
	//	pos[1] = float(pos1.y);
	//	pos[2] = float(pos1.z);
	//	glLightfv(GL_LIGHT1, GL_POSITION, pos);
	//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1->inverseTransformOf(Vec(0,0,1)));

	//	// Point light
	//	Vec pos2 = light2->position();
	//	pos[0] = float(pos2.x);
	//	pos[1] = float(pos2.y);
	//	pos[2] = float(pos2.z);
	//	glLightfv(GL_LIGHT2, GL_POSITION, pos);

	//	// Draws the spiral
	//	const float nbSteps = 200.0;
	//	glBegin(GL_QUAD_STRIP);
	//	for (float i=0; i<nbSteps; ++i)
	//	{
	//		float ratio = i/nbSteps;
	//		float angle = 21.0*ratio;
	//		float c = cos(angle);
	//		float s = sin(angle);
	//		float r1 = 1.0 - 0.8*ratio;
	//		float r2 = 0.8 - 0.8*ratio;
	//		float alt = ratio - 0.5;
	//		const float nor = .5;
	//		const float up = sqrt(1.0-nor*nor);
	//		glColor3f(1-ratio, 0.2f , ratio);
	//		glNormal3f(nor*c, up, nor*s);
	//		glVertex3f(r1*c, alt, r1*s);
	//		glVertex3f(r2*c, alt+0.05, r2*s);
	//	}
	//	glEnd();

	//	drawLight(GL_LIGHT0);

	//	if (light1->grabsMouse())
	//		drawLight(GL_LIGHT1, 1.2f);
	//	else
	//		drawLight(GL_LIGHT1);

	//	if (light2->grabsMouse())
	//		drawLight(GL_LIGHT2, 1.2f);
	//	else
	//		drawLight(GL_LIGHT2);
	//}
void MeshViewer::draw()
{
	if (input_mesh.polygons.size()>0)
	{
		float pos[4] = {1.0, 0.5, 1.0, 0.0};
		// Directionnal light
		glLightfv(GL_LIGHT0, GL_POSITION, pos);

		pos[3] = 1.0;
		// Spot light
		Vec pos1 = light1->position();
		pos[0] = float(pos1.x);
		pos[1] = float(pos1.y);
		pos[2] = float(pos1.z);
		glLightfv(GL_LIGHT1, GL_POSITION, pos);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1->inverseTransformOf(Vec(0,0,1)));

		// Point light
		Vec pos2 = light2->position();
		pos[0] = float(pos2.x);
		pos[1] = float(pos2.y);
		pos[2] = float(pos2.z);
		glLightfv(GL_LIGHT2, GL_POSITION, pos);
		
		
		for(std::vector< ::pcl::Vertices>::iterator tri=input_mesh.polygons.begin();tri!=input_mesh.polygons.end();tri++)
		{
			pcl::PointNormal p1,p2,p3;
			p1=cloud->points[(*tri).vertices[0]];
			p2=cloud->points[(*tri).vertices[1]];
			p3=cloud->points[(*tri).vertices[2]];
			glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(p1.normal_x,p1.normal_y,p1.normal_z);
			glVertex3f(p1.x,p1.y,p1.z);
			glNormal3f(p2.normal_x,p2.normal_y,p2.normal_z);
			glVertex3f(p2.x,p2.y,p2.z);
			glNormal3f(p3.normal_x,p3.normal_y,p3.normal_z);
			glVertex3f(p3.x,p3.y,p3.z);
			glEnd();
		}
		drawLight(GL_LIGHT0);
		
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Light0 is the default ambient light
	glEnable(GL_LIGHT0);

	// Light1 is a spot light
	glEnable(GL_LIGHT1);
	const GLfloat light_ambient[4]  = {0.8f, 0.2f, 0.2f, 1.0};
	const GLfloat light_diffuse[4]  = {1.0, 0.4f, 0.4f, 1.0};
	const GLfloat light_specular[4] = {1.0, 0.0, 0.0, 1.0};

	glLightf( GL_LIGHT1, GL_SPOT_EXPONENT,  3.0);
	glLightf( GL_LIGHT1, GL_SPOT_CUTOFF,    20.0);
	glLightf( GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf( GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.0);
	glLightf( GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 1.5);
	glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);

	// Light2 is a classical directionnal light
	glEnable(GL_LIGHT2);
	const GLfloat light_ambient2[4]  = {0.2f, 0.2f, 2.0, 1.0};
	const GLfloat light_diffuse2[4]  = {0.8f, 0.8f, 1.0, 1.0};
	const GLfloat light_specular2[4] = {0.0, 0.0, 1.0, 1.0};

	glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_diffuse2);

	light1 = new ManipulatedFrame();
	light2 = new ManipulatedFrame();
	setMouseTracking(true);

	light1->setPosition(0.5, 0.5, 0);
	// Align z axis with -position direction : look at scene center
	light1->setOrientation(Quaternion(Vec(0,0,1), -light1->position()));

	light2->setPosition(-0.5, 0.5, 0);

	restoreStateFromFile();
	
}



void MeshViewer::setMeshBuffer(pcl::PolygonMesh &input)
{
	input_mesh=input;
	pcl::fromPCLPointCloud2<pcl::PointNormal>(input_mesh.cloud,*cloud);
	/*pcl::NormalEstimation<pcl::PointNormal,pcl::PointNormal>::Ptr ne(new pcl::NormalEstimation<pcl::PointNormal,pcl::PointNormal> ());
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree(new pcl::search::KdTree<pcl::PointNormal> ()) ;

	ne->setInputCloud(cloud);
	ne->setSearchMethod(tree);
	ne->setRadiusSearch (0.5);
	ne->compute (*normal);*/
	cout<<"done"<<endl;
}

