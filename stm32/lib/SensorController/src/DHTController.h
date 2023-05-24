#ifndef DHTCONTROLLER_H
#define DHTCONTROLLER_H
#include "DHT.h"

#include <STM32FreeRTOS.h>
#include <Taskbase.h>
class DHTController : public TaskClass
{
public:
  DHTController();
  void setPin(int pin);
  int getTemperature();
  int getHumidity();

private:
  int _pin = -1;
  DHT _dht;
  int _temperature;
  int _humidity;
  xTaskHandle _threadHandler;
  void setTemperature(int temperature);
  void setHumidity(int humidity);
  void readSensorTask() override;
};

#endif