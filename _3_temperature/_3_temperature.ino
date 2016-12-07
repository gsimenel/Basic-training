#include <Arduino.h>
#include <Wire.h>
#include <HTS221.h>

double temperature;
long poll_interval = 900000; // 15 minutes in ms

void setup() {
  // Initiate USB and Sigfox
  SerialUSB.begin(115200);
  while(!SerialUSB) {}
  SigFox.begin(19200);
  SigFox.print("+++");
  SerialUSB.println("Sigfox ready");
  Wire.begin();
  if (!smeHumidity.begin()) { // Flash red light if there is an error initializing the sensor
    SerialUSB.println("ERROR w/ temperature");;
  }
  else {
    SerialUSB.println("Temperature sensor OK");
  }
  
  // Wait for everything to setlle
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  temperature = smeHumidity.readTemperature();
  // Copy the value
  float fval = (float)temperature;
  // Use pointer to access each Byte in memory
  byte* array = (byte*) &fval; 

  // Let's send the command to Sigfox 
  SigFox.print("AT$SF=");
  for (int i = 3; i >= 0; i--) {
    SigFox.print(array [i], HEX); 
  }
  SigFox.print("\r");
  SerialUSB.println("Message sent");

  delay(poll_interval);
}
