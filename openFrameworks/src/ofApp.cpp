#include "ofApp.h"

constexpr const char *PROJECT_NAME = "Untitled";
constexpr const char *CREATOR = "Violet Graham";

void ofApp::setup() {
  plotter.setup();
  ofxOPlot::Program program;

  program.addDirective(ofxOPlot::makeStartDirective());
  program.addDirective(ofxOPlot::makeHomeDirective());

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
