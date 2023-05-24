#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include <DHTController.h>
#include <MQController.h>


class SensorController : protected DHTController, protected MQController
{
public:
  SensorController();
  void setDHTpin(int pin);
  void setMQpin(int pin);
  void setLDRpin(int pin);

  int getCO2();
  int getTVOC();
  float getTemperature();
  float getHumidity();
  int getCO();
  int getLPG();
  int getSmoke();

private:

  // DHTController _dhtController;
  // MQController _mqController;
  // int _dht_pin;
  int _mq_pin;
  int _sgp_pin;
  int _ldr_pin;

  int _co2;
  int _tvoc;
  // float _temperature;
  // float _humidity;
  int _co;
  int _lpg;
  int _smoke;

  // void _readDHT();
  void _readMQ();
  void _readSGP();
  void _readLDR();
};

#endif