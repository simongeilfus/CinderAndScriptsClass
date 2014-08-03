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

//! console wrapper
void print( const std::string &s )
{
    console() << s << endl;
}

void HelloAngelscriptApp::setup()
{
    // get a reference to our global engine.
    // somehow a bad design in my wrapper, but make everything easier
    asIScriptEngine* engine = as::Script::getEngine();
    
    // bind our first function. you'll notice that Angelscript allows
    // us to keep const correctness in our script interface.
    engine->RegisterGlobalFunction("void print( const string &in )", asFUNCTION(print), asCALL_CDECL, this );
    
    
    // same as previous example, load the script from the asset folder
    as::ScriptRef script = as::Script::create( loadAsset( "Hello.script" ), "" );
    
    // now that we have a print function in the script, no need do anything
    // else from outside except calling our hello function
    script->call<string>( "void hello()" );
    
    // clear out the window with black
	getWindow()->getSignalDraw().connect( [this] { gl::clear(); } );
}

CINDER_APP_NATIVE( HelloAngelscriptApp, RendererGl )
