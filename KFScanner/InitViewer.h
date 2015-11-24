#ifndef INITVIEWER_H
#define INITVIEWER_H

#include <QGLViewer/qglviewer.h>

class QPaintEvent;
class QPainter;

class InitViewer : public QGLViewer
{
public :
	InitViewer(QWidget* parent = 0);

protected :
	virtual void draw();
	virtual void init();
	void drawLegend(QPainter *painter);
	virtual void paintGL() { update(); };
	virtual void paintEvent(QPaintEvent *event);
	// Could be overloaded to defer final initializations
	//virtual void showEvent(QShowEvent *event);

	virtual QString helpString() const;
public:
	void updateStates(bool,bool,bool);
private:
	bool kinect_state;
	bool facility_state;
	bool GPU_state;
};
#endif // INITVIEWER_H
