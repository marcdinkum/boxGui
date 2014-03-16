#include "testApp.h"


void testApp::setup()
{
  oscHost=ofSystemTextBoxDialog("Host",OSC_REMOTE_HOST);

  margin=3; // space around each 'button'

  float rectWidth=(ofGetWidth()-(cols+1)*margin)/cols;
  float rectHeight=(ofGetHeight()-(rows+1)*margin)/rows;

  ofSetFrameRate(30);

  currentRow=15;
  idleColor=ofColor(100,175,175);
  activeColor=ofColor(200,225,225);
  // selected row
  idleRowColor=ofColor(75,200,150);
  activeRowColor=ofColor(50,255,255);

  for(int row=0; row<rows; row++){
    for(int col=0; col<cols; col++){
      matrix[row][col].setGeometry(col*rectWidth+(col+1)*margin,
          row*rectHeight+(row+1)*margin,rectWidth,rectHeight);
      if(row==currentRow)
        matrix[row][col].setColors(idleRowColor,activeRowColor);
      else
        matrix[row][col].setColors(idleColor,activeColor);
    } // for
  } // for

  // send registration message to server
  oscReceiver.setup(OSC_RECEIVE_PORT);
  oscSender.setup(oscHost,OSC_REMOTE_PORT);
  ofxOscMessage m;
  m.setAddress("/register");
  oscSender.sendMessage(m);
} // setup


void testApp::exit()
{
} // exit()


void testApp::update()
{
ofxOscMessage msg;
int row,col,status;

  // pull all messages from the queue
  while(oscReceiver.getNextMessage(&msg))
  {
    if(msg.getAddress() == "/box/status") {
      row=msg.getArgAsInt32(0);
      col=msg.getArgAsInt32(1);
      status=msg.getArgAsInt32(2);
      if(row >= rows || col >= cols) continue; // ignore illegal row/col
      if(row < 0 || col < 0) continue; // ignore illegal row/col
      matrix[row][col].setStatus(status);
    } // if
  } // while

} // update()


void testApp::draw()
{
  for(int row=0; row<rows; row++){
    for(int col=0; col<cols; col++){
      matrix[row][col].draw();
    } // for
  } // for
} // draw()


void testApp::keyPressed(int key)
{
bool carry,status;

  switch(key)
  {
    case OF_KEY_DOWN:
      for(int col=0; col<cols; col++)
        matrix[currentRow][col].setColors(idleColor,activeColor);
      currentRow = (currentRow+1)%rows;
      for(int col=0; col<cols; col++)
        matrix[currentRow][col].setColors(idleRowColor,activeRowColor);
    return;
    case OF_KEY_UP:
      for(int col=0; col<cols; col++)
        matrix[currentRow][col].setColors(idleColor,activeColor);
      if(currentRow==0) currentRow=rows-1;
      else currentRow = (currentRow-1)%rows;
      cout << currentRow << endl;
      for(int col=0; col<cols; col++)
        matrix[currentRow][col].setColors(idleRowColor,activeRowColor);
    return;
    case OF_KEY_LEFT:
      carry=matrix[currentRow][0].getStatus();
      for(int col=0; col<cols-1; col++)
        matrix[currentRow][col].setStatus(matrix[currentRow][col+1].getStatus());
      matrix[currentRow][cols-1].setStatus(carry);
    break;
    case OF_KEY_RIGHT:
      carry=matrix[currentRow][cols-1].getStatus();
      for(int col=cols-1; col>0; col--)
        matrix[currentRow][col].setStatus(matrix[currentRow][col-1].getStatus());
      matrix[currentRow][0].setStatus(carry);
    break;
    case ' ':
      for(int col=0; col<cols; col++)
        matrix[currentRow][col].setStatus(false);
    break;
    case 'i':
      for(int col=0; col<cols; col++)
        matrix[currentRow][col].setStatus(!matrix[currentRow][col].getStatus());
    break;
    case 'r': // (re-)register
      ofxOscMessage m;
      m.setAddress("/register");
      oscSender.sendMessage(m);
    break;
  } // switch
  for(int col=0; col<cols; col++){
    status=matrix[currentRow][col].getStatus();
    ofxOscMessage m;
    m.setAddress("/box/setstatus");
    m.addIntArg(currentRow);
    m.addIntArg(col);
    m.addIntArg(status);
    oscSender.sendMessage(m);
  } // for
} // keyPressed()


void testApp::keyReleased(int key)
{
}

void testApp::mouseMoved(int x, int y )
{
}

void testApp::mouseDragged(int x, int y, int button)
{
bool newstatus;

  for(int row=0; row<rows; row++){
    for(int col=0; col<cols; col++){
      if(matrix[row][col].pointerIsIn(mouseX,mouseY)){
        newstatus = !button ? 1 : 0;
	matrix[row][col].setStatus(newstatus);
	ofxOscMessage m;
	m.setAddress("/box/setstatus");
	m.addIntArg(row);
	m.addIntArg(col);
	m.addIntArg(newstatus);
	oscSender.sendMessage(m);
      } // if
    } // for
  } // for
}

void testApp::mousePressed(int x, int y, int button)
{
bool status;

  for(int row=0; row<rows; row++){
    for(int col=0; col<cols; col++){
      if(matrix[row][col].pointerIsIn(mouseX,mouseY)){
        status=matrix[row][col].toggleStatus();
	ofxOscMessage m;
	m.setAddress("/box/setstatus");
	m.addIntArg(row);
	m.addIntArg(col);
	m.addIntArg(status);
	oscSender.sendMessage(m);
      } // if
    } // for
  } // for
} // mousePressed()


void testApp::mouseReleased(int x, int y, int button)
{
}

void testApp::windowResized(int w, int h)
{
float rectWidth=(w-(cols+1)*margin)/cols;
float rectHeight=(h-(rows+1)*margin)/rows;

  for(int row=0; row<rows; row++){
    for(int col=0; col<cols; col++){
      matrix[row][col].setGeometry(col*rectWidth+(col+1)*margin,
          row*rectHeight+(row+1)*margin,rectWidth,rectHeight);
    } // for
  } // for

}

void testApp::gotMessage(ofMessage msg)
{
}

void testApp::dragEvent(ofDragInfo dragInfo)
{ 
}
