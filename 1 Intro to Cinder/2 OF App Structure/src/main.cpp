#include "cinder/Cinder.h"
#include "ofApp.h"

using namespace cinder::app;

int main( int argc, char * const argv[] ) {
    AppBasic::prepareLaunch();
    AppBasic *app = new ofApp();
    RendererRef ren( new RendererGl() );
    AppBasic::executeLaunch( app, ren, "ofApp", argc, argv );
    AppBasic::cleanupLaunch();
    return 0;
}


/*
 // How it looks in Openframeworks
 
 

 #include "ofMain.h"
 #include "ofApp.h"
 
 //========================================================================
 int main( ){
 
 ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context
 
 // this kicks off the running of my app
 // can be OF_WINDOW or OF_FULLSCREEN
 // pass in width and height too:
 ofRunApp( new ofApp());
 
 }



*/