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
    
    //! our draw Script
    lua::ScriptRef mScript;
};

void ScriptApp::setup()
{
    AssetManager::load( "draw.lua", [this]( DataSourceRef script ){
        
        try {
            mScript = lua::Script::create( script );
        }
        catch( const luabind::error &err ){
            cout << err.what() << endl;
        }
        catch( const std::exception &exc ){
            cout << exc.what() << endl;
        }
        catch( ... ){
        }
        
    });
    
}


void ScriptApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    // if the script got loaded and compiled correctly
    if( mScript ){
        mScript->call( "draw" );
    }
}

CINDER_APP_NATIVE( ScriptApp, RendererGl )
