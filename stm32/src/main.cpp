#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "DHT.h"
#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>
#include <SoftwareSerial.h>

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


void setup()
{
  chat.begin(4800);
  Serial.begin(9600);

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

  
}

int counter = 0;
void loop()
{
  //delay(dht.getMinimumSamplingPeriod());

  //float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  //float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ

  //Serial.print(dht.getStatusString());
  //Serial.print("\t");
  //Serial.print(humidity, 1);
  //Serial.print("\t\t");
  //Serial.print(temperature, 1);
  //Serial.print("\t\t");
  //Serial.println(dht.toFahrenheit(temperature), 1);

  //First fifteen readings will be
  //CO2: 400 ppm  TVOC: 0 ppb
  //delay(1000); //Wait 1 second
  //measure CO2 and TVOC levels
  //mySensor.measureAirQuality();
  //Serial.print("CO2: ");
  //Serial.print(mySensor.CO2);
  //Serial.print(" ppm\tTVOC: ");
  //Serial.print(mySensor.TVOC);
  //Serial.println(" ppb");
  //delay(1000);
   if (chat.readString()){
    Serial.println("Chat recv!!");
     if(chat.readString()== "Q1"){ //มีการถามคำถาม Question1 ส่งข้อมูลตัวแปร a ออกไป
        delay(dht.getMinimumSamplingPeriod());

        float humidity = dht.getHumidity(); // ดึงค่าความชื้น
        float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ

        //chat.print(dht.getStatusString());
        chat.println(humidity);
        Serial.println(humidity);
        //chat.print(temperature);
        //chat.print(dht.toFahrenheit(temperature));

     }

     else if(chat.readString()== "Q2"){ //มีการถามคำถาม Question2 ส่งข้อมูลตัวแปร b ออกไป

      chat.print(b);

     }

      Serial.print("Send = ");

      Serial.println(i);

  }

  i++;
  delay(1000);
}

