#ifndef LEDCONTROLLER_H_
#define LEDCONTROLLER_H_
#include "Arduino.h"

typedef unsigned int pinNum;

enum Color
{
  RED,
  GREEN,
  BLUE,
  YELLOW,
  CYAN,
  MAGENTA,
  BLACK,
  WHITE
};

class LedController {
public:
  void init(pinNum red, pinNum green, pinNum blue);
  void setColor(unsigned short red, unsigned short green, unsigned short blue);
  void setColor(Color color);

private:
  pinNum ledRed;
  pinNum ledGreen;
  pinNum ledBlue;
};

#endif