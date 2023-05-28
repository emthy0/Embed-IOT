#include <ServoController.h>

ServoController::ServoController(char* name)
{
    #ifdef SERVO_PIN
        this->setPin(SERVO_PIN);
    #endif
    this->setAngle(0);
}

void ServoController::setPin(int pin)
{
    _pin = pin;
    _servo.attach(_pin);
}

void ServoController::setAngle(int angle)
{
    // if (angle == _angle)
    // {
    //     return;
    // }
    angle = max(0, min(180, angle));
    if (angle < _angle)
    {
        for (int i = _angle; i > angle; i--)
        {
            Serial.println(i);
            _servo.write(i);
            delay(150);
            // vTaskDelay(150);
        }
    } else {
        for (int i = _angle; i < angle; i++)
        {
            Serial.println(i);
            _servo.write(i);
            delay(150);
            // vTaskDelay(150);
        }
    }
    _angle = angle;

}

int ServoController::getAngle()
{
    return _angle;
}

void ServoController::classTask()
{
    if (_pin != -1)
    {
        this->setAngle(_angle);
        vTaskDelay(1000);
    }
}