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
    
    // create a script that represents a function named "hello"
    lua::ScriptRef func = lua::Script::create( "function hello()\
                                                    return 'Lua'\
                                              end" );
    
    // call the "hello" function from Lua and get back the string
    // as a const char* and output it to the console
    console() << "Hello " << func->call<const char*>( "hello" ) << endl;
    
    // clear out the window with black
	getWindow()->getSignalDraw().connect( [this] { gl::clear(); } );
}

CINDER_APP_NATIVE( HelloLuaApp, RendererGl )
