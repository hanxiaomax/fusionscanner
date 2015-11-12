#include "CloudViewer.h"
#include <iostream>

using namespace std;

void CloudViewer::update(vertexes pcd)
{
	pcd_buffer=pcd;//_scanner->getPointCloud();;
	updateGL();
}

void CloudViewer::draw() 
{
	
	glPushMatrix();
	//glScaled(vizScale,vizScale,vizScale);
	//glMultMatrixd(m_global_transform.data());

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
	for (int i = 0; i < pcd_buffer.size(); ++i) 
	{
		glVertex3dv(&(pcd_buffer[i].y));
	}
	glEnd();

	//std::cout<<"update"<<std::endl;

	
}

void CloudViewer::init() {
	// Restore previous viewer state.
	restoreStateFromFile();

    setFPSIsDisplayed();

	setSceneBoundingBox(qglviewer::Vec(-50,-50,-50), qglviewer::Vec(50,50,50));

	showEntireScene();
}
