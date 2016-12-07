#include <Arduino.h>
#include <Wire.h>

void setup() {
  // Initiate USB and Sigfox
  SerialUSB.begin(115200);
  while(!SerialUSB) {}
  SigFox.begin(19200);
  SigFox.print("+++");
  SerialUSB.println("Sigfox ready");
  
  // Wait for everything to setlle
  delay(500);

  // Let's run this once only, so we keep it in setup
  SigFox.print("AT$SF=CAFECAFE,1");
  SigFox.print("\r");
  SerialUSB.println("Message sent");
  
}

void loop() {
  while (SigFox.available()) {
    SerialUSB.write(SigFox.read());
  }


}
