#ifndef SENSORCLASS_H
#define SENSORCLASS_H

class SensorClass
{
public:
  virtual void setPin(int pin) = 0;
  virtual int getTemperature() = 0;
  virtual int getHumidity() = 0;
  virtual int getCO() = 0;
  virtual int getLPG() = 0;
  virtual int getSmoke() = 0;
};

#endif