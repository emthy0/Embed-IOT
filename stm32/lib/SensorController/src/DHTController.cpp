#include <DHTController.h>
#include "DHT.h"
#include <GlobalSensorValue.h>

DHTController::DHTController() : TaskClass("DHT Thread", 1000, 1000)
{
}

void DHTController::setPin(int pin)
{
  _pin = pin;
  _dht.setup(_pin);
}

void DHTController::_setTemperature(int temperature)
{
  _temperature = temperature;
}

void DHTController::_setHumidity(int humidity)
{
  _humidity = humidity;
  #if GLOBAL_HUMIDITY != 0
      GLOBAL_HUMIDITY = humidity;
  #endif
  
}

int DHTController::getTemperature()
{
  return _temperature;
}

int DHTController::getHumidity()
{
  return _humidity;
}

void DHTController::classTask()
{
  if (_pin != -1)
  {
    this->_setTemperature(_dht.getTemperature());
    this->_setHumidity(_dht.getHumidity());
    vTaskDelay(_dht.getMinimumSamplingPeriod());
  }
  
}

// void DHTController : Taskbase::taskfun(void *params)
// {
//   static_cast<DHTController *>(params)->readSensorThread();
// }