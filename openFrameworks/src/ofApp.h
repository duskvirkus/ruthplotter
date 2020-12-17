#pragma once

#include "ofMain.h"
#include "ofxOPlot.h"
#include <cmath>
class ofApp : public ofBaseApp {

public:
  ofxOPlot::Machine plotter;

  void setup();
  void update();
  void draw();

  void title();
};
