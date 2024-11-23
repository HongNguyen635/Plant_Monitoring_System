//this is slave

#include <SoftwareSerial.h>

#define PHOTOCELL_CHAR 'A'
#define TEMP_CHAR 'B'
#define MOISTURE_CHAR 'C'
#define TEMP_SOIL_CHAR 'D'
#define IR_SENSOR1 'E'
#define IR_SENSOR2 'F'

SoftwareSerial BTSerial(10, 11); // RX, TX

// setup serial monitor and bluetooth
// also test the onboard LED
void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

// test bluetooth to read msg from mega
void loop() 
{
  if (BTSerial.available()) {
    char BT = BTSerial.read();
    if (BT == PHOTOCELL_CHAR) {
      Serial.println(analogRead(A0));
      uint16_t photocell = analogRead(A0);
      Serial.println(photocell);
      uint8_t hi = photocell >> 8;
      uint8_t lo = photocell & 0xFF;
      BTSerial.write(hi);
      while (!BTSerial.available()) {}
      BTSerial.write(lo);
    } else if (BT == TEMP_CHAR) {
      BTSerial.write(analogRead(A1));
      Serial.println(analogRead(A1));
    } else if (BT == MOISTURE_CHAR) {
      BTSerial.write(MOISTURE_CHAR);
    } else if (BT == TEMP_SOIL_CHAR) {
      BTSerial.write(TEMP_SOIL_CHAR);
    } else if (BT == IR_SENSOR1) {
      if (digitalRead(2) == HIGH) {
        BTSerial.write('H');
      } else {
        BTSerial.write('L');
      }
    } else if (BT == IR_SENSOR2) {
      if (digitalRead(3) == HIGH) {
        BTSerial.write('H');
      } else {
        BTSerial.write('L');
      }
    } else {
      Serial.println("char not recognized");
    }
  }
}
