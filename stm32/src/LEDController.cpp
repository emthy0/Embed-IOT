#include <LEDController.h>
#include <Arduino.h>
#include <TaskBase.h>

LEDController::LEDController(int pin) : TaskClass("LED Thread", 1, 1000)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    this->_mode = OFF;
}

void LEDController::execute(char* command[3])
{
    char* rawAction = command[0];
    String parsedCommand = String(rawAction[0]) + String(rawAction[1]) + String(rawAction[2]) + String(rawAction[3]);
    //Serial.println(parsedCommand);
    if (parsedCommand == "acti")
    {
        this->activate();
    }
    else if (parsedCommand == "deac")
    {
        this->deactivate();
    }
    
    // xTaskCreate(LEDController::classTask, "ledThread", 128, (void *)*this, 1, NULL)
}

void LEDController::activate()
{
    this->_mode = ON;
    Serial.println("LED ON");
    if (this->_mode == ON)
        {
            //digitalWrite(_pin, HIGH);
            digitalWrite(PB5, HIGH);
        }
        else
        {
            //digitalWrite(_pin, LOW);
            digitalWrite(PB5, LOW);
        }

}

void LEDController::deactivate()
{
    this->_mode = OFF;
    Serial.println("LED OFF");
    if (this->_mode == ON)
        {
            //digitalWrite(_pin, HIGH);
            digitalWrite(PB5, HIGH);
        }
        else
        {
            //digitalWrite(_pin, LOW);
            digitalWrite(PB5, LOW);
        }
}

void LEDController::classTask()
{

        if (this->_mode == ON)
        {
            //digitalWrite(_pin, HIGH);
            digitalWrite(PB5, HIGH);
        }
        else
        {
            //digitalWrite(_pin, LOW);
            digitalWrite(PB5, LOW);
        }
        vTaskDelete(NULL);
    
}
