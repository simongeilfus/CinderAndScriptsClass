#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Script.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HelloLuaApp : public AppNative {
  public:
	void setup();
};

void HelloLuaApp::setup()
{
    // create a script that get executed directly
    lua::Script::create( "print 'Hello Lua'" );
    
    
    // clear out the window with black
	getWindow()->getSignalDraw().connect( [this] { gl::clear(); } );
}

CINDER_APP_NATIVE( HelloLuaApp, RendererGl )
