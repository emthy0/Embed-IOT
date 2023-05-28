#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "DHT.h"
#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>
#include <SoftwareSerial.h>
#include <servo.h>
Servo myServo;
SGP30 mySensor; //create an object of the SGP30 class
DHT dht;

#define ESP_RX PA1
#define ESP_TX PA4
#define DHT_PIN PA0_ALT1

// #define GAS_PIN = 
SoftwareSerial chat(ESP_RX,ESP_TX); // RX, TX to NodeMCU
int i;

int a = 13;
int b = 25;

// define task
void servoThread(void *pvParameters);
bool servoOn = true;
int servoPos = 0;

void setup()
{
  chat.begin(4800);
  Serial.begin(9600);
    myServo.attach(PC7);
  // myServo.write(90);
  // delay(1000);
  // myServo.write(0);
  // while (!Serial); // wait for serial port to connect. Needed for native USB port only
  
  // Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

  dht.setup(DHT_PIN); // data pin 2

  //Wire.begin();
  //Initialize sensor
  //if (mySensor.begin(Wire) == false) {
  //  Serial.println("No SGP30 Detected. Check connections.");
  //  while (1);
  //}
  //Initializes sensor for air quality readings
  //measureAirQuality should be called in one second increments after a call to 
  //mySensor.initAirQuality();

  // setup task
  // xTaskCreate(servoThread, "servoThread2", 128, NULL, 1, NULL);
  // vTaskStartScheduler();
  
}

int counter = 0;
void loop()
{
    //   myServo.write(10);
//     myServo.write(0);
//     delay(1000);
//     myServo.write(90);
// delay(1000);
    for (servoPos = 0; servoPos <= 90; servoPos += 1) { 
        myServo.write(servoPos);
        Serial.println(servoPos);                
        delay(15);                       
    }
    Serial.println("to 2nd for");
    for (servoPos = 90; servoPos >= 0; servoPos -= 1) { 
        myServo.write(servoPos); 
        Serial.println(servoPos);        
        delay(15);                       
    }
}


// task for servo motor
void servoThread(void * pvParameters){

  // setup

  (void) pvParameters;


  // loop
  while(true){
    if (servoOn == false) {
      vTaskDelay(15);
      continue;
    }
    myServo.write(10);
    vTaskDelay(1000);
    myServo.write(45);
    myServo.write(90);
    // for (servoPos = 0; servoPos <= 90; servoPos += 1) { 
    //     myServo.write(servoPos);
    //     Serial.println(servoPos);                
    //     vTaskDelay(15);                       
    // }
    // Serial.println("to 2nd for");
    // for (servoPos = 90; servoPos >= 0; servoPos -= 1) { 
    //     myServo.write(servoPos); 
    //     Serial.println(servoPos);        
    //     vTaskDelay(15);                       
    // }
  }
}