#include <DHTController.h>
#include "DHT.h"

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
}

int DHTController::getTemperature()
{
  return _dht.getTemperature();
}

int DHTController::getHumidity()
{
  return _dht.getHumidity();
}

void DHTController::readSensorTask()
{
  if (_pin == -1)
  {
    return;
  }
  this->_setTemperature(_dht.getTemperature());
  this->_setHumidity(_dht.getHumidity());
  vTaskDelay(1000);
}

// void DHTController : Taskbase::taskfun(void *params)
// {
//   static_cast<DHTController *>(params)->readSensorThread();
// }