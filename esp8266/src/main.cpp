// #include <Arduino.h>
// #include <Wire.h>
// #include <ESP8266WiFi.h>

// // TwoWire Wire;
// #define STM_ADDRESS 0x08

// void setup()
// {
//   Wire.pins(D6, D5); // I2C2 SDA, SCL D6, D5
//   Wire.begin(D6, D5); //
//   Serial.begin(9600);
// }

// void loop()
// {
//   Wire.requestFrom(STM_ADDRESS, 1);
//   byte a;
//   Wire.readBytes(&a,1);
//   if (a == 1)
//   {
//     Serial.println("Master LED ON");
//   }
//   else
//   {
//     Serial.println(a);
//   }
//   Wire.beginTransmission(STM_ADDRESS);
//   Wire.write('v');
//   Wire.endTransmission();
//   delay(1000);
// }
#include <Arduino.h>
#include <Wire.h>


void setup() {

  Serial.begin(9600);
  Wire.begin(D6, D5);
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.

    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("done");

  delay(5000);           // wait 5 seconds for next scan
}