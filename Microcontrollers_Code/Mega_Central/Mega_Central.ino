//this is master
#include <TimerOne.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// components pins
#define displaySDA 20
#define displaySCL 21

// bluetooth assigned char
#define PHOTOCELL_CHAR 'A'
#define TEMP_CHAR 'B'
#define MOISTURE_CHAR 'C'
#define TEMP_SOIL_CHAR 'D'
#define IR_SENSOR1 'E'
#define IR_SENSOR2 'F'

int counter = 0;

int photocellReading = 0;
int tempReading = 0;
int moistureReading = 0;
int tempSoilReading = 0;

int photocellPeriod = 1;
int tempPeriod = 2;
int moisturePeriod = 3;
int tempSoilPeriod = 4;

bool readPhotocell = false;
bool readTemp = false;
bool readMoisture = false;
bool readTempSoil = false;

// setup bluetooth
SoftwareSerial BTSerial(12, 2); // RX, TX

// set up display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// set up the baud rate for bluetooth
void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);
  lcd.backlight();
  lcd.init(); 
  // Serial.println("works");
  Timer1.initialize(1000000);
  // Serial.println("works");
  Timer1.attachInterrupt(sensorCheck);
  Serial.println("works");
}

// test communication to uno
void loop()
{
  // BTSerial.write('1');

  // test display
  // lcd.clear();
  // lcd.setCursor(0, 0); 
  // lcd.print("Test message");




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

  // int Temp = requestTemp();
  // Serial.println(Temp);

  // bool IR1 = requestIR1();
  // if (IR1) {
  //   Serial.println("object present");
  // }

  // bool IR2 = requestIR2();
  // if (IR2) {
  //   Serial.println("object present");
  // }
  if (readPhotocell) {
    requestPhotocell();
    Serial.print("Photocell Reading: ");
    Serial.println(photocellReading);
    readPhotocell = false;
  }
  if (readTemp) {
    requestTemp();
    Serial.print("temperature Reading: ");
    Serial.println(tempReading);
    readTemp = false;
  }
  if (readMoisture) {
    requestMoisture();
    Serial.print("moisture Reading: ");
    Serial.println(moistureReading);
    readMoisture = false;
  }
  if (readTempSoil) {
    requestTempSoil();
    Serial.print("soil temp Reading: ");
    Serial.println(tempSoilReading);
    readTempSoil = false;
  }
}

void sensorCheck(void) {
  counter++;
  if ((counter % photocellPeriod == 0)) {
    // requestPhotocell();
    readPhotocell = true;
  }
  if ((counter % tempPeriod == 0)) {
    // requestTemp();
    readTemp = true;
  }
  if ((counter % moisturePeriod == 0)) {
    // requestMoisture();
    readMoisture = true;
  }
  if ((counter % tempSoilPeriod == 0)) {
    // requestTempSoil();
    readTempSoil = true;
  } 
  Serial.println();
}

void requestPhotocell(void) {
  BTSerial.write(PHOTOCELL_CHAR);
  // while (!BTSerial.available()) {}
  uint8_t hi = BTSerial.read();
  // BTSerial.write('0');
  // while (!BTSerial.available()) {}
  uint8_t lo = BTSerial.read();
  uint16_t BT = (hi << 8) + lo;
  photocellReading = BT;
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

void requestTemp(void) {
  BTSerial.write(TEMP_CHAR);
  // while (!BTSerial.available()) {}
  int BT = BTSerial.read();
  tempReading = BT;
}

void requestTempSoil(void) {
  tempSoilReading = 0;
}

void requestMoisture(void) {
  moistureReading = 0;
}
