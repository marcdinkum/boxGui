#include "testApp.h"


void testApp::setup()
{
  rowSlider.addListener(this,&testApp::rowSliderChanged);
  columnSlider.addListener(this,&testApp::columnSliderChanged);
  boxButton.addListener(this,&testApp::boxButtonPressed);

  controlPanel.setup();
  controlPanel.add(rowSlider.setup("Rij",0,0,7,300,20));
  controlPanel.add(columnSlider.setup("Kolom",0,0,15,300,20 ));
  controlPanel.add(boxButton.setup("Switch box on"));
  controlPanel.setPosition(0.3*ofGetWidth(),0.4*ofGetHeight());

  oscSender.setup(OSC_REMOTE_HOST,OSC_REMOTE_PORT);
} // setup


void testApp::exit()
{
  boxButton.removeListener(this,&testApp::boxButtonPressed);
} // exit()


void testApp::rowSliderChanged(int& row)
{
  this->row=row;
  cout << "row " << row << endl;
} // rowSliderChanged()


void testApp::columnSliderChanged(int& column)
{
  this->column=column;
  cout << "column " << column << endl;
} // columnSliderChanged()


void testApp::boxButtonPressed()
{
  cout << "Auw\n";
  ofxOscMessage m;
  m.setAddress("/box/setstatus");
  m.addIntArg(row);
  m.addIntArg(column);
  m.addIntArg(1);
  oscSender.sendMessage(m);
} // boxButtonPressed


void testApp::update()
{
} // update()


void testApp::draw()
{
  ofBackgroundGradient(ofColor::white,ofColor::gray);
  controlPanel.draw();
} // draw()


void testApp::keyPressed(int key)
{
}

void testApp::keyReleased(int key)
{
}

void testApp::mouseMoved(int x, int y )
{
}

void testApp::mouseDragged(int x, int y, int button)
{
}

void testApp::mousePressed(int x, int y, int button)
{
}

void testApp::mouseReleased(int x, int y, int button)
{
}

void testApp::windowResized(int w, int h)
{
}

void testApp::gotMessage(ofMessage msg)
{
}

void testApp::dragEvent(ofDragInfo dragInfo)
{ 
}
