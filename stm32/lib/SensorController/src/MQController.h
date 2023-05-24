#ifndef MQCONTROLLER_H
#define MQCONTROLLER_H
#include "MQ.h"
class MQController
{
public:
  MQController();
  void setPin(int pin);
  int getCO();
  int getLPG();
  int getSmoke();

private:
  int _pin = -1;
  int _MQ;
}

#endif