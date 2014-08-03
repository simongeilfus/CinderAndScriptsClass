#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"

#include "AssetManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ScriptApp : public AppNative {
  public:
	void setup();
	void draw();
    
    gl::Texture mTexture;
};

void ScriptApp::setup()
{
    // adds a secondary asset folder so we can share
    // assets between apps.
    addAssetDirectory( "../../../../../assets/" );
    
    AssetManager::load( "cinder_logo_alpha.png", [this]( DataSourceRef tex ) {
        
        mTexture = gl::Texture( loadImage( tex ) );
        
    } );
    
    gl::enableAlphaBlending();
    
}


void ScriptApp::draw()
{
	// clear out the window with black
	gl::clear( Color::white() );
    
    if( mTexture ){
        gl::draw( mTexture );
    }
}

CINDER_APP_NATIVE( ScriptApp, RendererGl )
