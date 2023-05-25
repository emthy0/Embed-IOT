#include <LDRController.h>
#include <Arduino.h>

LDRController::LDRController()
// : TaskClass("LDR Thread",1000,1000)
{
}

void LDRController::setPin(int pin)
{
    pinMode(pin,INPUT);
    _pin = pin;
}

void LDRController::_setBrightness(BRIGHTNESSS brightness)
{
    _brightness = brightness;
}

BRIGHTNESSS LDRController::getBrightness()

{
     if (_pin != -1 ) 
    {
    int value; 
    value = analogRead(_pin);  
    if (value < 50) {
        _brightness = NIGGA;
    } else if (value < 200) {
        _brightness = CHOCO;
    } else if (value < 500) {
        _brightness = YELLOWMONKEY;
    } else if (value < 800) {
        _brightness = KAREN;
    } else {
        _brightness = BECKY;
    }
    }
    return  _brightness;
}

void LDRController::classTask() {
    if (_pin != -1 ) 
    {
    int value; 
    value = analogRead(_pin);  
    if (value < 50) {
        _brightness = NIGGA;
    } else if (value < 200) {
        _brightness = CHOCO;
    } else if (value < 500) {
        _brightness = YELLOWMONKEY;
    } else if (value < 800) {
        _brightness = KAREN;
    } else {
        _brightness = BECKY;
    }
    }
    vTaskDelay(1000);

}