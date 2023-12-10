#ifndef LEDCONTROLLER_H_
#define LEDCONTROLLER_H_
#include "Arduino.h"

typedef unsigned int PinNum;

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
  void init(PinNum red, PinNum green, PinNum blue);
  void setColor(unsigned short red, unsigned short green, unsigned short blue);
  void setColor(Color color);

private:
  PinNum ledRed;
  PinNum ledGreen;
  PinNum ledBlue;
};

#endif