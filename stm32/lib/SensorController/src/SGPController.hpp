#ifndef SGPCONTROLLER_H
#define SGPCONTROLLER_H

#include "SparkFun_SGP30_Arduino_Library.h" 
#include <STM32FreeRTOS.h>
#include <Taskbase.h>
#include <Wire.h>

class SGPController : protected TaskClass
{
public:
  SGPController();
//   void setPin(int pin);
  int getCO2();
  int getTVOC();
private:
    SGP30 _sgpSensor;
    // int _pin = -1;
    int _co2 = -1;
    int _tvoc = -1;
    void _setCO2(int co2);
    void _setTVOC(int tvoc);
    void readSensorTask() override;
}