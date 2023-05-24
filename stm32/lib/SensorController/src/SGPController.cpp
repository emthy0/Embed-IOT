#include <SGPController.hpp>

SGPController::SGPController() : TaskClass("SGP Thread", 1000, 1000)
{
    _sgpSensor.begin();
    _sgpSensor.initAirQuality();
    _sgpSensor.setHumidity(50);
}

// void SGPController::setPin(int pin)

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

void SGPController::readSensorTask()
{
    _sgpSensor.measureAirQuality();
    _setCO2(_sgpSensor.CO2);
    _setTVOC(_sgpSensor.TVOC);
    vTaskDelay(1000);
}
