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

template<typename T>
void toString( T num ){
    return ...;
}


toString<int>( 5 );

void HelloAngelscriptApp::setup()
{
    // create a script that represents a function named "hello"
    // by default this angelscript wrapper doesn't execute the code loaded.
    // you have to call the function and cast what the function returns to
    // a string. You also have to specify the full function signature and
    // not only its name.
    
    as::ScriptRef script = as::Script::create( "string who(){\
                       return \"Angelscript\";\
                       }", "" );
    
    console() << "Hello " << script->call<string>( "string who()" ) << endl;
    
    // clear out the window with black
	getWindow()->getSignalDraw().connect( [this] { gl::clear(); } );
}

CINDER_APP_NATIVE( HelloAngelscriptApp, RendererGl )
