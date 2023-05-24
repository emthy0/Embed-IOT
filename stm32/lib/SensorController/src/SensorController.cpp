#include <SensorController.h>

SensorController::SensorController() : DHTController(), MQController(), SGPController(), LDRController()
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
    LDRController::setPin(pin);
}

int SensorController::getCO2()
{
    return SGPController::getCO2();
}

int SensorController::getTVOC()
{
    return SGPController::getTVOC();
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



