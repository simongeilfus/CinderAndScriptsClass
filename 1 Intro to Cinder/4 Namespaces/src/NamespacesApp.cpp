#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Point.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NamespacesApp : public AppNative {
  public:
	void setup();
};

void NamespacesApp::setup()
{
    gaw::Point point;
}

CINDER_APP_NATIVE( NamespacesApp, RendererGl )
