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

void SensorController::setSGPpin(int pin)
{
    _sgp_pin = pin;
}

void SensorController::setLDRpin(int pin)
{
    _ldr_pin = pin;
}


void SensorController::getTemperature()
{
    return DHTController::getTemperature();
}

void SensorController::getHumidity()
{
    return DHTController::getHumidity();
}

void SensorController::getCO()
{
    return MQController::getCO();
}

void SensorController::getLPG()
{
    return MQController::getLPG();
}

void SensorController::getSmoke()
{
    return MQController::getSmoke();
}

