#include "ofApp.h"

constexpr const char *PROJECT_NAME = "Untitled";
constexpr const char *CREATOR = "Violet Graham";

void ofApp::setup() {
  plotter.setup();
  ofxOPlot::Program program;

  program.addDirective(ofxOPlot::makeStartDirective());
  program.addDirective(ofxOPlot::makeHomeDirective());

  int r = 100;
  for (int i = 0; i < 32; i++) {
    float a = ofMap(i, 0, 31, 0, TWO_PI);
    float x = r * cos(a);
    float y = r * sin(a);
    x += 200;
    y += 200;
    if (i == 0) {
      program.addDirective(ofxOPlot::makeMoveDirective(x, y));
    } else {
      program.addDirective(ofxOPlot::makeMarkDirective(x, y));
    }
  }

  plotter.loadProgram(program);
}

void ofApp::update() {
  title();
  plotter.update();
}

void ofApp::draw() {}

void ofApp::title() {
  stringstream titleStream;
  titleStream << PROJECT_NAME << " - " << CREATOR
              << " - FPS: " << static_cast<int>(ofGetFrameRate());
  ofSetWindowTitle(titleStream.str());
}
