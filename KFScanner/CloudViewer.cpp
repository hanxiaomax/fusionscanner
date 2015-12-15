#include "CloudViewer.h"
#include <iostream>

using namespace std;


void CloudViewer::draw() 
{
	if(pcd_buffer_->size()>0)
	{
		setFPSIsDisplayed();
		glPushMatrix();
		glScaled(vizScale,vizScale,vizScale);//缩放比例
		glDisable(GL_LIGHTING);
		//glPointSize(5.0f);
	
		glColor3f(1,1,0);
		glBegin(GL_POINTS);
		for (int i = 0; i < pcd_buffer_->size(); ++i) 
			glVertex3d(pcd_buffer_->points[i].x,pcd_buffer_->points[i].y,pcd_buffer_->points[i].z);//绘制一个点
		glEnd();
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		qglColor(QColor(255,255,255));
		QFont font("Microsoft YaHei",25,20);
		
		drawText(width()/2-140,height()/2,tr("没有可显示的点云"),font);
		glPopMatrix();
	}

}

void CloudViewer::init() {
	// Restore previous viewer state.
	restoreStateFromFile();

    

	setSceneBoundingBox(qglviewer::Vec(-50,-50,-50), qglviewer::Vec(50,50,50));

	showEntireScene();
	vizScale=80.0f;
}
