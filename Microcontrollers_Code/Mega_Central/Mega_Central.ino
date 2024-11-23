//this is master

#include <SoftwareSerial.h>

#define PHOTOCELL_CHAR 'A'
#define TEMP_CHAR 'B'
#define MOISTURE_CHAR 'C'
#define TEMP_SOIL_CHAR 'D'
#define IR_SENSOR1 'E'
#define IR_SENSOR2 'F'

// setup bluetooth
SoftwareSerial BTSerial(12, 2); // RX, TX

// set up the baud rate for bluetooth
void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);
}

// test communication to uno
void loop()
{
  // BTSerial.write('B');
  // while (!BTSerial.available()) {}
  // char BT = BTSerial.read();
  // if (BT == 'PHOTOCELL_CHAR') {
  //   Serial.println("received data");
  // } else {
  //   Serial.println("incorrect data received");
  // }
  // delay(100);

  // int photocell = requestPhotocell();
  // Serial.println(photocell);

  int Temp = requestTemp();
  Serial.println(Temp);

  // bool IR1 = requestIR1();
  // if (IR1) {
  //   Serial.println("object present");
  // }

  // bool IR2 = requestIR2();
  // if (IR2) {
  //   Serial.println("object present");
  // }
}

int requestPhotocell() {
  BTSerial.write(PHOTOCELL_CHAR);
  while (!BTSerial.available()) {}
  uint8_t hi = BTSerial.read();
  BTSerial.write('0');
  while (!BTSerial.available()) {}
  uint8_t lo = BTSerial.read();
  uint16_t BT = (hi << 8) + lo;
  return BT;
}

bool requestIR1() {
  BTSerial.write(IR_SENSOR1);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  return !(BT == 'H');
}

bool requestIR2() {
  BTSerial.write(IR_SENSOR2);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  return !(BT == 'H');
}

int requestTemp() {
  BTSerial.write(TEMP_CHAR);
  while (!BTSerial.available()) {}
  int BT = BTSerial.read();
  return BT;
}

int requestTempSoil() {

}

int requestMoisture() {

}
