#include <SensorController.h>

SensorController::SensorController() : DHTController(), MQController()
{

}

void SensorController::setDHTpin(int pin)
{
    DHTController::setPin(pin);
}

void SensorController::setMQpin(int pin)
{
    MQController::setPin(pin);
}


void SensorController::setLDRpin(int pin)
{
    _ldr_pin = pin;
}


float SensorController::getTemperature()
{
    return DHTController::getTemperature();
}

float SensorController::getHumidity()
{
    return DHTController::getHumidity();
}

int SensorController::getCO()
{
    return MQController::getCO();
}

int SensorController::getLPG()
{
    return MQController::getLPG();
}

int SensorController::getSmoke()
{
    return MQController::getSmoke();
}



