#include <SGPController.h>
#include <GlobalSensorValue.h>

SGPController::SGPController() : TaskClass("SGP Thread", 1000, 1000)
{
  Wire.begin();
  _sgpSensor.begin();
  _sgpSensor.initAirQuality();
  _sgpSensor.setHumidity(50);
}

// void SGPController::setPin(int pin)
void SGPController::setHumidity(int humidity)
{
  _sgpSensor.setHumidity(humidity);
}

int SGPController::getCO2()
{
  return _co2;
}

int SGPController::getTVOC()
{
  return _tvoc;
}

void SGPController::_setCO2(int co2)
{
  _co2 = co2;
}

void SGPController::_setTVOC(int tvoc)
{
  _tvoc = tvoc;
}

void SGPController::classTask()
{
#ifdef GLOBAL_HUMIDITY
  this->setHumidity(GLOBAL_HUMIDITY);
#endif
  _sgpSensor.measureAirQuality();
  _setCO2(_sgpSensor.CO2);
  _setTVOC(_sgpSensor.TVOC);
  vTaskDelay(1000);
}
