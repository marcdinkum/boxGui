#include <ofMain.h>

class MatrixButton
{
public:
  MatrixButton();
  void setGeometry(float x,float y,float width,float height);
  void setColors(ofColor idleColor,ofColor activeColor);
  void setStatus(bool status);
  bool toggleStatus();
  bool getStatus();
  bool pointerIsIn(float x,float y);
  void draw();
private:
  bool status;
  float x,y,width,height;
  ofColor idleColor,activeColor;
};
