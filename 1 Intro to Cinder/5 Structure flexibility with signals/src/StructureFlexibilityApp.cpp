#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class StructureFlexibilityApp : public AppNative {
  public:
	void setup();
};

void StructureFlexibilityApp::setup()
{
    // get a reference to the main window
    // so we can attach different signals to it
    WindowRef window = getWindow();
    
    // the usual draw function
	window->getSignalDraw().connect( [this] {
        // clear out the window with black
        gl::clear( Color( 0, 0, 0 ) );
    } );
    
    // mouse down
	window->getSignalMouseDown().connect( [this] ( MouseEvent event ){
    } );
    
    // and the signal that got fired when this window is closed
	window->getSignalClose().connect( [this] {
    } );
}


CINDER_APP_NATIVE( StructureFlexibilityApp, RendererGl )
