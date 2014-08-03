#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

class ofApp : public ci::app::AppNative {
  public:
	void setup();
	void update();
	void draw();
	void mouseDown( ci::app::MouseEvent event );
    
};


/*
 // How it looks in Openframeworks

 
 #include "ofMain.h"
 
 class ofApp : public ofBaseApp{
 public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);

 };


*/