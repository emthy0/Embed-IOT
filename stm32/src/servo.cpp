#include <Arduino.h>
#include <servo.h>
#include <STM32FreeRTOS.h>

Servo myServo;
int pos = 0;

// task for servo motor
void servoThread(void * pvParameters){

  // setup
  (void) pvParameters;
  myServo.attach(PC7);

  // loop
  while(true){
    for (pos = 0; pos <= 180; pos += 1) { 
        myServo.write(pos);             
        vTaskDelay(15);                       
    }
    for (pos = 180; pos >= 0; pos -= 1) { 
        myServo.write(pos);             
        vTaskDelay(15);                       
    }
  }
}