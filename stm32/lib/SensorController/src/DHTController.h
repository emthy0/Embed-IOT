#ifndef DHTCONTROLLER_H
#define DHTCONTROLLER_H
#include "DHT.h"

#include <STM32FreeRTOS.h>
#include <Taskbase.h>
class DHTController : protected TaskClass
{
public:
  DHTController();
  void setPin(int pin);
  int getTemperature();
  int getHumidity();

private:
  int _pin = -1;
  DHT _dht;
  int _temperature = -1;
  int _humidity = -1;
  void _setTemperature(int temperature);
  void _setHumidity(int humidity);
  void classTask();
};

#endif