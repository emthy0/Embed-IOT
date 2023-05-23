#include "DHT.h"
#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>
#include <STM32FreeRTOS.h>
 
SGP30 mySensor; //create an object of the SGP30 class
DHT dht;

int a = 13;
int b = 25;
#include <SoftwareSerial.h>
#define ESP_RX  PA8
#define ESP_TX PA7_ALT1
#define DHT_PIN PA0_ALT1
// #define GAS_PIN = 
#define BUZZER_PIN PA0
SoftwareSerial chat(ESP_RX,ESP_TX); // RX, TX to NodeMCU
int i;

// define tasks
void buzzerThread(void *pvParameters); // if buzzerOn is true, the buzzer will buzz
bool buzzerOn = false;

void setup()
{
  chat.begin(4800);
  Serial.begin(9600);
  //Serial.println();
  //Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

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
  xTaskCreate(buzzerThread, "buzzerThread", 128, NULL, 1, NULL);
  vTaskStartScheduler();
  
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
     if(chat.readString()== "Q1"){ //มีการถามคำถาม Question1 ส่งข้อมูลตัวแปร a ออกไป
        delay(dht.getMinimumSamplingPeriod());

        float humidity = dht.getHumidity(); // ดึงค่าความชื้น
        float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ

        //chat.print(dht.getStatusString());
        chat.print(humidity);
        Serial.print(humidity);
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

// tasks
void buzzerThread(void * pvParameters){

  (void) pvParameters;
  pinMode(BUZZER_PIN, OUTPUT);

  while(true){
    if (buzzerOn){
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(10);
      digitalWrite(BUZZER_PIN, LOW);
      vTaskDelay(10);
    }
    else{
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
}