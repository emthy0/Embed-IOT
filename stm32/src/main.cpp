#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <HardwareSerial.h>
HardwareSerial Serial6(PA_12, PA_11); // RX | TX

void setup()
{
  Serial.begin(9600);
  Serial6.begin(4800);
}

void loop()
{
  while (Serial6.available() > 0)
  {
    float val = Serial6.parseFloat();
    if (Serial6.read() == '\n')
    {
      Serial.println(val);
    }
  }
  delay(100);
}