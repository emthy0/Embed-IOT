#ifndef DHTCONTROLLER_H
#define DHTCONTROLLER_H
#include "DHT.h"
#include <STM32FreeRTOS.h>
class DHTController
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
    xTaskHandle _thread;
    void setTemperature(int temperature);
    void setHumidity(int humidity);
    void readSensorThread(void *pvParameters);
};

#endif