#include <DHTController.h>
#include "DHT.h"

DHTController::DHTController() : TaskClass("DHT Thread", 1000, 1000)
{
  //  if (_thread.joinable())
  // {
  //   _thread.join();
  // }
  // else {

  // }
  // TaskClass("DHT Thread", 1000, 1000);
  // xTaskCreate(&DHTController::readSensorThread, "DHT Thread", 1000, (void *)this, 1, &_thread);
}

// DHTController::~DHTController()
// {
//   if (_thread.joinable())
//   {
//     _thread.join();
//   }
// }

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

void DHTController::readSensorTask()
{
  //   DHTController *dhtController = static_cast<DHTController *>();
  //   dhtController->setTemperature(dhtController->getTemperature());
  //   dhtController->setHumidity(dhtController->getHumidity());
  this->setTemperature(this->getTemperature());
  this->setHumidity(this->getHumidity());
  vTaskDelay(1000);
}

// void DHTController : Taskbase::taskfun(void *params)
// {
//   static_cast<DHTController *>(params)->readSensorThread();
// }