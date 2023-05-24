#include <DHTController.h>
#include "DHT.h"

void DHTController::readSensorThread(void *pvParameters)
{
}

DHTController::DHTController()
{
  xTaskCreate(&DHT::readSensorThread, "DHT Thread", 1000, (void *)&this, 1, &_thread);
}

DHTController::~DHTController(int pin)
{
  if (_thread.joinable())
  {
    _thread.join();
  }
}

void DHTController::setPin(int pin)
{
  _pin = pin;
  _dht.setup(_pin);
}

void DHTController::setTemperature(int temperature)
{
  _temperature = temperature;
}

void DHTController::setHumidity(int humidity)
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

