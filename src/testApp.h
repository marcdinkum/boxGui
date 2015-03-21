#pragma once

#include <ofMain.h>
#include <ofxOsc.h>
#include "matrixButton.h"

#define OSC_REMOTE_HOST "127.0.0.1"
#define OSC_REMOTE_PORT 7777
#define OSC_RECEIVE_PORT 7778

#define ROWS 16
#define COLUMNS 16

class testApp : public ofBaseApp{
	
public:
  void setup();
  void exit();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);		

private:
  string oscHost;
  int rows,columns;
  float margin;
  int currentRow;
  ofColor idleColor,activeColor,idleRowColor,activeRowColor;

  ofxOscSender oscSender;
  ofxOscReceiver oscReceiver;

  MatrixButton matrix[ROWS][COLUMNS];
};

