//this is slave

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX, TX

// setup serial monitor and bluetooth
// also test the onboard LED
void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

// test bluetooth to read msg from mega
void loop() 
{
  if (BTSerial.available()) {
    Serial.println(BTSerial.read() - '0');
  }
}
