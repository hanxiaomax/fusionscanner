#include "InitViewer.h"


#include <QMenu>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMap>
#include <QCursor>

#include <math.h>

using namespace std;

// Draws a spiral
void InitViewer::draw()
{ 
  const float nbSteps = 80.0;
  
  glBegin(GL_QUAD_STRIP);
  for (float i=0; i<nbSteps; ++i)
	{
	  
	  float ratio = i/nbSteps;
	  float angle = 21.0*ratio;
	  float c = cos(angle);
	  float s = sin(angle);
	  float r1 = 1.0 - 0.8*ratio;
	  float r2 = 0.8 - 0.8*ratio;
	  float alt = ratio - 0.5;
	  const float nor = .5;
	  const float up = sqrt(1.0-nor*nor);
	  glColor3f(fabs(c), 0.2f, fabs(s));
	  glNormal3f(nor*c, up, nor*s);
	  glVertex3f(r1*c, alt, r1*s);
	  glVertex3f(r2*c, alt+0.05, r2*s);
	}
  glEnd();
  
}

void InitViewer::init()
{
  // Restore previous viewer state.
  restoreStateFromFile();


  /////////////////////////////////////////////////////
  //       Keyboard shortcut customization           //
  //      Changes standard action key bindings       //
  /////////////////////////////////////////////////////

  // Define 'Control+Q' as the new exit shortcut (default was 'Escape')
  setShortcut(EXIT_VIEWER, Qt::CTRL+Qt::Key_Q);

  // Set 'Control+F' as the FPS toggle state key.
  setShortcut(DISPLAY_FPS, Qt::CTRL+Qt::Key_F);

  // Disable draw grid toggle shortcut (default was 'G')
  setShortcut(DRAW_GRID, 0);


  // Add custom key description (see keyPressEvent).
  setKeyDescription(Qt::Key_W, "Toggles wire frame display");
  setKeyDescription(Qt::Key_F, "Toggles flat shading display");


  /////////////////////////////////////////////////////
  //         Mouse bindings customization            //
  //     Changes standard action mouse bindings      //
  /////////////////////////////////////////////////////

  // Left and right buttons together make a camera zoom : emulates a mouse third button if needed.
  setMouseBinding(Qt::Key_Z, Qt::NoModifier, Qt::LeftButton, CAMERA, ZOOM);

  // Disable previous TRANSLATE mouse binding (and remove it from help mouse tab).
  setMouseBinding(Qt::NoModifier, Qt::RightButton, NO_CLICK_ACTION);

  setMouseBinding(Qt::ControlModifier | Qt::ShiftModifier, Qt::RightButton, SELECT);
  setWheelBinding(Qt::AltModifier, CAMERA, MOVE_FORWARD);
  setMouseBinding(Qt::AltModifier, Qt::LeftButton, CAMERA, TRANSLATE);

  // Add custom mouse bindings description (see mousePressEvent())
  setMouseBindingDescription(Qt::NoModifier, Qt::RightButton, "Opens a camera path context menu");
}


///////////////////////////////////////////////
//      Define new key bindings : F & W      //
///////////////////////////////////////////////

void InitViewer::keyPressEvent(QKeyEvent *e)
{
  // Get event modifiers key
  const Qt::KeyboardModifiers modifiers = e->modifiers();

  // A simple switch on e->key() is not sufficient if we want to take state key into account.
  // With a switch, it would have been impossible to separate 'F' from 'CTRL+F'.
  // That's why we use imbricated if...else and a "handled" boolean.
  bool handled = false;
  if ((e->key()==Qt::Key_W) && (modifiers==Qt::NoButton))
	{
	  wireframe_ = !wireframe_;
	  if (wireframe_)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	  else
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	  handled = true;
	  updateGL();
	}
  else
	if ((e->key()==Qt::Key_F) && (modifiers==Qt::NoButton))
	  {
	flatShading_ = !flatShading_;
	if (flatShading_)
	  glShadeModel(GL_FLAT);
	else
	  glShadeModel(GL_SMOOTH);
	handled = true;
	updateGL();
	  }
  // ... and so on with other else/if blocks.

  if (!handled)
	QGLViewer::keyPressEvent(e);
}


///////////////////////////////////////////////////////////
//             Define new mouse bindings                 //
//   A camera viewpoint menu binded on right button      //
///////////////////////////////////////////////////////////

void InitViewer::mousePressEvent(QMouseEvent* e)
{
  if ((e->button() == Qt::RightButton) && (e->modifiers() == Qt::NoButton))
	{
	  QMenu menu( this );
	  menu.addAction("Camera positions");
	  menu.addSeparator();
	  QMap<QAction*, int> menuMap;

	  bool atLeastOne = false;
	  // We only test the 20 first indexes. This is a limitation.
	  for (unsigned short i=0; i<20; ++i)
	if (camera()->keyFrameInterpolator(i))
	  {
		atLeastOne = true;
		QString text;
		if (camera()->keyFrameInterpolator(i)->numberOfKeyFrames() == 1)
		  text = "Position "+QString::number(i);
		else
		  text = "Path "+QString::number(i);

		menuMap[menu.addAction(text)] = i;
	  }

	  if (!atLeastOne)
	{
	  menu.addAction("No position defined");
	  menu.addAction("Use to Alt+Fx to define one");
	}

	  QAction* action = menu.exec(e->globalPos());

	  if (atLeastOne && action)
		  camera()->playPath(menuMap[action]);
	}
  else
	QGLViewer::mousePressEvent(e);
}
