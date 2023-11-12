#include "Arduino.h"
#include "LedController.h"

void LedController::init(pinNum red, pinNum green, pinNum blue)
{
  this->ledRed = red;
  this->ledGreen = green;
  this->ledBlue = blue;
}

void LedController::setColor(unsigned short red, unsigned short green, unsigned short blue)
{
  analogWrite(ledRed, red);
  analogWrite(ledGreen, green);
  analogWrite(ledBlue, blue);
}

void LedController::setColor(Color color) {
  switch (color) {
  case RED: {
    setColor(255, 0, 0);
    break;
  }
  case GREEN: {
    setColor(0, 255, 0);
    break;
  }
  case BLUE: {
    setColor(0, 0, 255);
    break;
  }
  case YELLOW: {
    setColor(255, 255, 0);
    break;
  }
  case CYAN: {
    setColor(0, 255, 255);
    break;
  }
  case MAGENTA: {
    setColor(255, 0, 255);
    break;
  }
  case BLACK: {
    setColor(0, 0, 0);
    break;
  }
  case WHITE: {
    setColor(255, 255, 255);
    break;
  }
  default: break;
  }
}