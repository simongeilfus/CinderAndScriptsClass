#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ObjectsAndPrimitivesApp : public AppNative {
  public:
	void draw();
};

void ObjectsAndPrimitivesApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::color( 1, 1, 1 );
    gl::drawSolidCircle( Vec2f( getWindowWidth() * 0.5f, getWindowHeight() * 0.5f ), 50.0f );
}

CINDER_APP_NATIVE( ObjectsAndPrimitivesApp, RendererGl )
