#pragma once

#include "ofMain.h"
#include "ofxOPlot.h"
class ofApp : public ofBaseApp {

public:
  ofxOPlot::Machine plotter;

  void setup();
  void update();
  void draw();

  void title();
};
