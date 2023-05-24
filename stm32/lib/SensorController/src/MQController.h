#ifndef MQCONTROLLER_H
#define MQCONTROLLER_H
#include "DHT.h"

#include <STM32FreeRTOS.h>
#include <Taskbase.h>
class MQController : protected TaskClass
{

public:
  MQController();
  void setPin(int pin);
  int getCO();
  int getLPG();
  int getSmoke();

private:
  int _pin = -1;
  int _co = -1;
  int _lpg = -1;
  int _smoke = -1;
  void _setCO(int co);
  void _setLPG(int lpg);
  void _setSmoke(int smoke);
  void classTask();

  int _READ_SAMPLE_TIMES = 5;
  float _LPGCurve[3] = {2.3, 0.21, -0.47};
  float _COCurve[3] = {2.3, 0.72, -0.34};
  float _SmokeCurve[3] = {2.3, 0.53, -0.44};
  float           _Ro           =  10;
  float           _RL_VALUE     =  5;
  float _MQResistanceCalculation(int raw_adc);
  float _MQCalibration(int mq_pin);
  float _MQRead();
};

#endif