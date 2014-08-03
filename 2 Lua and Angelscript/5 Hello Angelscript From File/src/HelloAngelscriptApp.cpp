#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Script.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HelloAngelscriptApp : public AppNative {
  public:
	void setup();
};

void HelloAngelscriptApp::setup()
{
    // same as previous example, exept we are loading the script from disk
    // and not from memory.
    as::ScriptRef script = as::Script::create( loadAsset( "Hello.script" ), "" );
    
    // call the "who" method and output what it returns.
    console() << "Hello " << script->call<string>( "string who()" ) << script->call<string>( "string test()" ) << endl;
    
    // clear out the window with black
	getWindow()->getSignalDraw().connect( [this] { gl::clear(); } );
}

CINDER_APP_NATIVE( HelloAngelscriptApp, RendererGl )
