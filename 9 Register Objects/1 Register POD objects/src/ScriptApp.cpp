#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Script.h"
#include "AssetManager.h"

#include "Registration.h"

using namespace ci;
using namespace ci::app;
using namespace std;


struct Obj {
    int     mX;
    int     mY;
    float   mSize;
};


class ScriptApp : public AppNative {
  public:
	void setup();
    void update();
	void draw();
    
    void mouseDown( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseUp( MouseEvent event );
    
    //! setup the engine, registers the app interface and load scripts
	void setupScriptEngine();
    
    //! console wrapper
    void print( const std::string &s );
    
    //! our script file
    as::ScriptRef mScript;
};

void ScriptApp::setup()
{
    getWindow()->setAlwaysOnTop();
    
    setupScriptEngine();
    
    // watch our sketch for change and reloads it when needed
    AssetManager::load( "main.script", [this]( DataSourceRef sketch ){
        mScript = as::Script::create( sketch, "" );
        
        if( mScript ){
            mScript->call( "void setup()" );
        }
    });
}

void ScriptApp::setupScriptEngine()
{
    // get a reference to our global engine.
    asIScriptEngine* engine = as::Script::getEngine();
    
    // register a print function. this time we check the return value which is a good practice
    // if we want to detect errors in writing the application interface.
    int r = engine->RegisterGlobalFunction("void print( const string &in )", asMETHOD(ScriptApp,print), asCALL_THISCALL_ASGLOBAL, this );  assert( r >= 0 );
    
    // register cinder
    as::registerCinder( engine );
    
    
    // register our simple struct
    r = engine->RegisterObjectType( "Obj", sizeof(Obj), asOBJ_VALUE | asOBJ_POD ); assert( r >= 0 );
    r = engine->RegisterObjectProperty( "Obj", "int mX", asOFFSET( Obj, mX ) ); assert( r >= 0 );
    r = engine->RegisterObjectProperty( "Obj", "int mY", asOFFSET( Obj, mY ) ); assert( r >= 0 );
    r = engine->RegisterObjectProperty( "Obj", "float mSize", asOFFSET( Obj, mSize ) ); assert( r >= 0 );
    
}


void ScriptApp::update()
{
    if( mScript ){
        mScript->call( "void update()" );
    }
}

void ScriptApp::draw()
{
    if( mScript ){
        mScript->call( "void draw()" );
    }
}

void ScriptApp::mouseDown( MouseEvent event )
{
    if( mScript ){
        mScript->call( "void mouseDown( MouseEvent event )", event );
    }
}

void ScriptApp::mouseUp( MouseEvent event )
{
    if( mScript ){
        mScript->call( "void mouseUp( MouseEvent event )", event );
    }
}

void ScriptApp::mouseDrag( MouseEvent event )
{
    if( mScript ){
        mScript->call( "void mouseDrag( MouseEvent event )", event );
    }
}

void ScriptApp::mouseMove( MouseEvent event )
{
    if( mScript ){
        mScript->call( "void mouseMove( MouseEvent event )", event );
    }
}

//! console wrapper
void ScriptApp::print( const std::string &s )
{
    console() << s << endl;
}

CINDER_APP_NATIVE( ScriptApp, RendererGl )
