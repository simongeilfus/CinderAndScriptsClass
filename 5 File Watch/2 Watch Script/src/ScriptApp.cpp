#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"


#include "Script.h"

#include "AssetManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ScriptApp : public AppNative {
  public:
	void setup();
	void draw();
    
    as::ScriptRef mScript;
};

void ScriptApp::setup()
{
    AssetManager::load( "main.script", [this]( DataSourceRef script ){
        mScript = as::Script::create( script, "" );
    } );
}


void ScriptApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( ScriptApp, RendererGl )
