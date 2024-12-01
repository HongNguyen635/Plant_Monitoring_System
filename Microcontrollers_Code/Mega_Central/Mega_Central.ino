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
#define IR_SENSOR3 'G'
#define IR_SENSOR4 'H'
#define HUMIDITY_CHAR 'I'

int counter = 0;

int photocellReading = 0;
int tempReading = 0;
int moistureReading = 0;
int tempSoilReading = 0;
bool IR1Reading = 0;
bool IR2Reading = 0;
bool IR3Reading = 0;
bool IR4Reading = 0;
int humidityReading = 0;

int photocellPeriod = 1;
int tempPeriod = 2;
int moisturePeriod = 3;
int tempSoilPeriod = 4;
int IR1Period = 1;
int IR2Period = 1;
int IR3Period = 1;
int IR4Period = 1;
int humidityPeriod = 5;

bool readPhotocell = false;
bool readTemp = false;
bool readMoisture = false;
bool readTempSoil = false;
bool readIR1 = false;
bool readIR2 = false;
bool readIR3 = false;
bool readIR4 = false;
bool readHumidity = false;

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
  if (readIR1) {
    requestIR1();
    if (IR1Reading == true) {
      Serial.println("IR1: object detected");
    } else {
      Serial.println("IR1: no object detected");
    }
    readIR1 = false;
  }
  if (readIR2) {
    requestIR2();
    if (IR2Reading == true) {
      Serial.println("IR2: object detected");
    } else {
      Serial.println("IR2: no object detected");
    }
    readIR2 = false;
  }
  if (readIR3) {
    requestIR3();
    if (IR3Reading == true) {
      Serial.println("IR3: object detected");
    } else {
      Serial.println("IR3: no object detected");
    }
    readIR3 = false;
  }
  if (readIR4) {
    requestIR4();
    if (IR4Reading == true) {
      Serial.println("IR4: object detected");
    } else {
      Serial.println("IR4: no object detected");
    }
    readIR4 = false;
  }
  if (readHumidity) {
    requestHumidity();
    Serial.print(humidityReading);
    Serial.println("\% humidity level");
    readHumidity = false;
  }
}

void sensorCheck(void) {
  counter++;
  if (counter % photocellPeriod == 0) {
    // requestPhotocell();
    readPhotocell = true;
  }
  if (counter % tempPeriod == 0) {
    // requestTemp();
    readTemp = true;
  }
  if (counter % moisturePeriod == 0) {
    // requestMoisture();
    readMoisture = true;
  }
  if (counter % tempSoilPeriod == 0) {
    // requestTempSoil();
    readTempSoil = true;
  } 
  if (counter % IR1Period == 0) {
    readIR1 = true;
  }
  if (counter % IR2Period == 0) {
    readIR2 = true;
  }
  if (counter % IR3Period == 0) {
    readIR3 = true;
  }
  if (counter % IR4Period == 0) {
    readIR4 = true;
  }
  if (counter % humidityPeriod == 0) {
    readHumidity = true;
  }
  Serial.println();
}


void requestPhotocell(void) {
  BTSerial.write(PHOTOCELL_CHAR);
  while (BTSerial.available() <  2) {}
  uint8_t hi = BTSerial.read();
  uint8_t lo = BTSerial.read();
  uint16_t BT = (hi << 8) | lo;
  photocellReading = BT;
}

void requestIR1() {
  BTSerial.write(IR_SENSOR1);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  IR1Reading = !(BT == 'H');
}

void requestIR2() {
  BTSerial.write(IR_SENSOR2);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  IR2Reading = !(BT == 'H');
}

void requestIR3() {
  BTSerial.write(IR_SENSOR3);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  IR3Reading = !(BT == 'H');
}

void requestIR4() {
  BTSerial.write(IR_SENSOR1);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  IR4Reading = !(BT == 'H');
}

void requestTemp(void) {
  BTSerial.write(TEMP_CHAR);
  while (!BTSerial.available()) {}
  int BT = BTSerial.read();
  tempReading = BT;
}

void requestTempSoil(void) {
  BTSerial.write(TEMP_SOIL_CHAR);
  while (!BTSerial.available()) {}
  int BT = BTSerial.read();
  tempSoilReading = BT;
}

void requestMoisture(void) {
  BTSerial.write(MOISTURE_CHAR);
  while (BTSerial.available() <  2) {}
  uint8_t hi = BTSerial.read();
  uint8_t lo = BTSerial.read();
  uint16_t BT = (hi << 8) | lo;
  moistureReading = BT;
}

void requestHumidity(void) {
  BTSerial.write(HUMIDITY_CHAR);
  while (!BTSerial.available()) {}
  int BT = BTSerial.read();
  humidityReading = BT;
}
