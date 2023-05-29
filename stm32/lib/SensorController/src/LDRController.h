#ifndef LDRCONTROLLER_H
#define LDRCONTROLLER_H

#include <STM32FreeRTOS.h>
#include <Taskbase.h>

enum BRIGHTNESS
{
    VERYDARK,
  DARK,
  DIM,
  BRIGHT,
  VERYBRIGHT
};

enum BRIGHTNESSS
{
    NIGGA,
  CHOCO,
  YELLOWMONKEY,
  KAREN,
  BECKY
};

class LDRController 
// : protected TaskClass
{
public:
  LDRController();
  void setPin(int pin);
  BRIGHTNESSS getBrightness();
private:
    int _pin;
    BRIGHTNESSS _brightness;
    void _setBrightness(BRIGHTNESSS   brightness);
    void classTask();
};


#endif