#include "CloudViewer.h"
#include <iostream>

using namespace std;

void CloudViewer::update()
{
	updateGL();
}

void CloudViewer::draw() 
{
	glPushMatrix();
	glScaled(vizScale,vizScale,vizScale);//缩放比例
	glDisable(GL_LIGHTING);
	//glPointSize(5.0f);
	
	glColor3f(1,1,0);
	glBegin(GL_POINTS);
	for (int i = 0; i < pcd_buffer.size(); ++i) 
	{
		glVertex3d(pcd_buffer[i].x,pcd_buffer[i].y,pcd_buffer[i].z);//绘制一个点
	}
	glEnd();
	glPopMatrix();

}

void CloudViewer::init() {
	// Restore previous viewer state.
	restoreStateFromFile();

    setFPSIsDisplayed();

	setSceneBoundingBox(qglviewer::Vec(-50,-50,-50), qglviewer::Vec(50,50,50));

	showEntireScene();
	vizScale=80.0f;
}
