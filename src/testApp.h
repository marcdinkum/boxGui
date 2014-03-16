#pragma once

#include <ofMain.h>
#include <ofxOsc.h>
#include "matrixButton.h"

#define OSC_REMOTE_HOST "127.0.0.1"
#define OSC_REMOTE_PORT 7777

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

  int rows=16,cols=14;
  float margin;
  int currentRow;
  ofColor idleColor,activeColor,idleRowColor,activeRowColor;

  ofxOscSender oscSender;
  ofxOscReceiver oscReceiver;

  MatrixButton matrix[16][14];

};

