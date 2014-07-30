#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class AngelscriptApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void AngelscriptApp::setup()
{
}

void AngelscriptApp::mouseDown( MouseEvent event )
{
}

void AngelscriptApp::update()
{
}

void AngelscriptApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( AngelscriptApp, RendererGl )
