#include "matrixButton.h"

MatrixButton::MatrixButton()
{
  status=false;
  idleColor=ofColor(50);
  activeColor=ofColor(255);
}

void MatrixButton::setGeometry(float x,float y,float width,float height)
{
  this->x=x;
  this->y=y;
  this->width=width;
  this->height=height;
}

void MatrixButton::setColors(ofColor idleColor,ofColor activeColor)
{
  this->idleColor=idleColor;
  this->activeColor=activeColor;
}

void MatrixButton::setStatus(bool status)
{
  this->status=status;
}

bool MatrixButton::toggleStatus()
{
  status=!status;
  return status;
}


bool MatrixButton::getStatus()
{
  return status;
}


bool MatrixButton::pointerIsIn(float x,float y)
{
  if(x>=this->x && x<=this->x+width &&
     y>=this->y && y<=this->y+height) return true;
  else return false;
}


void MatrixButton::draw()
{
  if(status)ofSetColor(activeColor);
  else ofSetColor(idleColor);
  ofRect(x,y,width,height);
}

