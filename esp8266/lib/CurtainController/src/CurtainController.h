#ifndef CURTAINCONTROLLER_H
#define CURTAINCONTROLLER_H

#include "Arduino.h"

class Morse
{
  public:
    0(int pin);
    void begin();
    void dot();
    void dash();
  private:
    int _pin;
};

#endif