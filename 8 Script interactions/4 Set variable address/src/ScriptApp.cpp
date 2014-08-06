#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Script.h"
#include "AssetManager.h"
#include "Registration.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ScriptApp : public AppNative {
  public:
	void setup();
    void update();
	void draw();
    
    //! setup the engine, registers the app interface and load scripts
	void setupScriptEngine();
    
    //! console wrapper
    void print( const std::string &s );
    
    //! our script file
    as::ScriptRef mScript;
    
    //! Variables that are read/write accessible in scripts
    Vec2f sPosition;
    Vec2f sMousePosition;
    float sTime;
};

void ScriptApp::setup()
{
    getWindow()->setAlwaysOnTop();
    
    setupScriptEngine();
    
    // set the addresses to the script variables (static method)
    // these are at the moment implemented as global variables that are
    // accessible accross each scripts. We could probably use access
    // masks or config group to change the behavior of this function
    as::Script::setAddress( "Vec2f sPosition", &sPosition );
    
    // by using const you can specify that a variable will be read only
    as::Script::setAddress( "const Vec2f sMousePosition", &sMousePosition );
    as::Script::setAddress( "const float sTime", &sTime );
    
    // watch our script for change and reloads it when needed
    AssetManager::load( "main.script", [this]( DataSourceRef sketch ){
        mScript = as::Script::create( sketch, "" );
        
        if( mScript ){
            mScript->call( "void setup()" );
        }
    });
}

void ScriptApp::update()
{
    sMousePosition  = getMousePos() - getWindowPos();
    sTime           = getElapsedSeconds();
    
    if( mScript ){
        mScript->call( "void update()" );
    }
}

void ScriptApp::draw()
{
    gl::clear( ColorA::black() );
    
    if( mScript ){
        gl::color( mScript->call<ColorA>( "ColorA getColor()" ) );
    }
    else {
        gl::color( ColorA( 1.0f, 0.35f, 0.3f, 1.0f ) );
    }
    gl::drawSolidCircle( sPosition, 150 );
    
}


void ScriptApp::setupScriptEngine()
{
    // get a reference to our global engine.
    asIScriptEngine* engine = as::Script::getEngine();
    
    // register a print function.
    int r = engine->RegisterGlobalFunction("void print( const string &in )", asMETHOD(ScriptApp,print), asCALL_THISCALL_ASGLOBAL, this );  assert( r >= 0 );
    
    // register cinder
    as::registerCinder( engine );
    
}

//! console wrapper
void ScriptApp::print( const std::string &s )
{
    console() << s << endl;
}

CINDER_APP_NATIVE( ScriptApp, RendererGl )
