#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Script.h"
#include "AssetManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ScriptApp : public AppNative {
public:
	void setup();
	void draw();
    
    //! our settings file
    lua::ScriptRef mSettings;
};

void ScriptApp::setup()
{
    // load the application settings
    mSettings = lua::Script::create( loadAsset( "Settings.script" ) );
    
    // if the script got loaded and compiled correctly
    if( mSettings ){
        
        // extract the settings to setup the app window
        setWindowSize( mSettings->get<Vec2i>( "windowSize" ) );
        setWindowPos( mSettings->get<Vec2i>( "windowPos" ) );
        
        // check if we need to go fullscreen
        setFullScreen( mSettings->get<bool>( "fullscreen" ) );
    }
}


void ScriptApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
}

CINDER_APP_NATIVE( ScriptApp, RendererGl )
