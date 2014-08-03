#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"

#include "AssetManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ScriptApp : public AppNative {
  public:
	void setup();
	void draw();
};

void ScriptApp::setup()
{
    // adds a secondary asset folder so we can share
    // assets between apps.
    addAssetDirectory( "../../../assets/" );
}


void ScriptApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( ScriptApp, RendererGl )
