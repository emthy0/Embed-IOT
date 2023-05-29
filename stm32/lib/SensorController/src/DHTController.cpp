#include <DHTController.h>
#include <pinconfig.h>
#include <DHT.h>
#define DHTTYPE DHT11 
#include <GlobalSensorValue.h>

DHTController::DHTController()
{
  #ifdef DHT_PIN
    _pin = DHT_PIN;
    setPin(_pin)
  #endif
  // _dht(_pin, DHTTYPE);
}

void DHTController::setPin(int pin)
{
  _pin = pin;
  _dht = DHT(_pin, DHTTYPE);
  _dht.begin();
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

float DHTController::getTemperature()
{
  float t = _dht.readTemperature();
  if (!isnan(t)) {
    _setTemperature(t);
  }
    
    return _temperature;
 
}

float DHTController::getHumidity()
{
  float h = _dht.readHumidity();
  if (!isnan(h)) {
    _setHumidity(h);
  }
    return _humidity;
  
}

void DHTController::classTask()
{
  if (_pin != -1)
  {
    this->getHumidity();
    this->getTemperature();
    vTaskDelay(1000);
  }
  
}

// const char* DHTController::getError()
// {
//   return _dht.getStatusString();
// }
// void DHTController : Taskbase::taskfun(void *params)
// {
//   static_cast<DHTController *>(params)->readSensorThread();
// }