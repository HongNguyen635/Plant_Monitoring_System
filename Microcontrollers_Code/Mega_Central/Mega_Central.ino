//this is master
#include <TimerOne.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// components pins
#define displaySDA 20
#define displaySCL 21
#define pumpPin 2

// bluetooth assigned char
#define PHOTOCELL_CHAR 'A'
#define TEMP_CHAR 'B'
#define MOISTURE_CHAR 'C'
#define TEMP_SOIL_CHAR 'D'
#define IR_SENSOR1 'E'
#define IR_SENSOR2 'F'
#define IR_SENSOR3 'G'
#define IR_SENSOR4 'H'
#define IR_SENSOR5 'Z'
#define INTRUSION_DETECTED_CHAR 'I'
#define AIR_QUALITY_CHAR 'J'
#define HUMIDITY_CHAR 'K'
#define SOUND_SENSOR 'L'
#define SMOKE_SENSOR 'M'
#define FLAME_SENSOR 'N'
#define WATER_CMD_CHAR 'O'
#define TOGGLE_LED_CHAR 'P'
#define LED_BRIGHTNESS_CHAR 'Q'
#define LED_RED_CHAR 'R'
#define LED_GREEN_CHAR 'S'
#define LED_BLUE_CHAR 'T'
#define LED_RGB_CHAR 'U'
#define BUZZER_CMD_CHAR 'V'
#define WRITE_DISPLAY_CHAR 'W'
#define CLEAR_DISPLAY_CHAR 'X'
#define CONFIG_CHAR 'Y'

int counter = 0;

bool pumpOn = false;
bool pumpOff = false;
int pumpStart = 0;

int photocellReading = 0;
int tempReading = 0;
int moistureReading = 0;
int tempSoilReading = 0;
bool IR1Reading = 0;
bool IR2Reading = 0;
bool IR3Reading = 0;
bool IR4Reading = 0;
bool IR5Reading = 0;
int humidityReading = 0;
bool smokeReading = 0;
bool flameReading = 0;

int photocellPeriod = 0;
int tempPeriod = 0;
int moisturePeriod = 0;
int tempSoilPeriod = 0;
int IR1Period = 1;
int IR2Period = 1;
int IR3Period = 1;
int IR4Period = 1;
int IR5Period = 1;
int humidityPeriod = 0;
int smokePeriod = 1;
int flamePeriod = 1;

bool readPhotocell = false;
bool readTemp = false;
bool readMoisture = false;
bool readTempSoil = false;
bool readIR1 = false;
bool readIR2 = false;
bool readIR3 = false;
bool readIR4 = false;
bool readIR5 = false;
bool readHumidity = false;
bool readSmoke = false;
bool readFlame = false;

// setup bluetooth
SoftwareSerial BTSerial(12, 2); // RX, TX

// set up display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// set up the baud rate for bluetooth
void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);
  Serial1.begin(9600); // Hardware UART
  lcd.backlight();
  lcd.init(); 
  // Serial.println("works");
  Timer1.initialize(1000000);
  // Serial.println("works");
  Timer1.attachInterrupt(sensorCheck);
  pinMode(pumpPin, OUTPUT);
}

// test communication to uno
void loop()
{
  // ----- ESP32 UART COM -----
  // receive cmd from esp32
  if (Serial1.available()) {
    // read in the char
    char cmd = Serial1.read();

    switch (cmd) {
      case CONFIG_CHAR:
      // TODO:
      break;

      case TEMP_CHAR:
      // TODO:
      break;

      case MOISTURE_CHAR:
      // TODO: note, esp32 expects moisture 1st, then temp
      break;

      case PHOTOCELL_CHAR:
      // TODO:
      break;

      case WATER_CMD_CHAR:
      // TODO:
      break;

      case TOGGLE_LED_CHAR:
      // TODO:
      break;

      case LED_BRIGHTNESS_CHAR:
      // TODO:
      break;

      case LED_RED_CHAR:
      // TODO:
      break;

      case LED_BLUE_CHAR:
      // TODO:
      break;

      case LED_GREEN_CHAR:
      // TODO:
      break;

      case LED_RGB_CHAR:
      // TODO:
      break;

      case BUZZER_CMD_CHAR:
      // TODO:
      break;

      case WRITE_DISPLAY_CHAR:
      // TODO:
      break;

      case CLEAR_DISPLAY_CHAR:
      // TODO:
      break;
    }
  }

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
  if (readIR5) {
    requestIR5();
    if (IR5Reading == true) {
      Serial.println("IR5: object detected");
    } else {
      Serial.println("IR5: no object detected");
    }
    readIR5 = false;
  }
  if (readHumidity) {
    requestHumidity();
    Serial.print(humidityReading);
    Serial.println("\% humidity level");
    readHumidity = false;
  }
  if (readSmoke) {
    requestSmoke();
    if (smokeReading == true) {
      Serial.println("smoke detected");
    } else {
      Serial.println("no smoke detected");
    }
    readSmoke = false;
  }
  if (readFlame) {
    requestFlame();
    if (flameReading == true) {
      Serial.println("flame detected");
    } else {
      Serial.println("no flame detected");
    }
    readFlame = false;
  }
  if (pumpOn) {
    pumpOff = true;
    pumpStart = counter;
    pumpOn = false;
    digitalWrite(pumpPin, HIGH);
  }
  if (pumpOff && counter - pumpStart >= 300) {
    pumpOff = false;
    digitalWrite(pumpPin, LOW);
  }
}

void sensorCheck(void) {
  counter++;
  if (counter % photocellPeriod == 0 && photocellPeriod > 0) {
    // requestPhotocell();
    readPhotocell = true;
  }
  if (counter % tempPeriod == 0 && tempPeriod > 0) {
    // requestTemp();
    readTemp = true;
  }
  if (counter % moisturePeriod == 0 && moisturePeriod > 0) {
    // requestMoisture();
    readMoisture = true;
  }
  if (counter % tempSoilPeriod == 0 && tempSoilPeriod > 0) {
    // requestTempSoil();
    readTempSoil = true;
  } 
  if (counter % IR1Period == 0 && IR1Period > 0) {
    readIR1 = true;
  }
  if (counter % IR2Period == 0 && IR2Period > 0) {
    readIR2 = true;
  }
  if (counter % IR3Period == 0 && IR3Period > 0) {
    readIR3 = true;
  }
  if (counter % IR4Period == 0 && IR4Period > 0) {
    readIR4 = true;
  }
  if (counter % IR5Period == 0 && IR5Period > 0) {
    readIR5 = true;
  }
  if (counter % humidityPeriod == 0 && humidityPeriod > 0) {
    readHumidity = true;
  }
  if (counter % smokePeriod == 0 && smokePeriod > 0) {
    readSmoke = true;
  }
  if (counter % flamePeriod == 0 && flamePeriod > 0) {
    readFlame = true;
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

  // convert to human-readable
  String newPhotocell = convertPhototocellSensor();

  // send to UART
  Serial1.print(PHOTOCELL_CHAR);
  Serial1.println(newPhotocell);
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
  BTSerial.write(IR_SENSOR4);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  IR4Reading = !(BT == 'H');
}

void requestIR5() {
  BTSerial.write(IR_SENSOR5);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  IR5Reading = !(BT == 'H');
}

void requestSmoke() {
  BTSerial.write(SMOKE_SENSOR);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  smokeReading = (BT == 'H');
}

void requestFlame() {
  BTSerial.write(FLAME_SENSOR);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  flameReading = (BT == 'H');
}

void requestTemp(void) {
  BTSerial.write(TEMP_CHAR);
  while (!BTSerial.available()) {}
  int BT = BTSerial.read();
  tempReading = BT;

  // convert to human-readable
  uint8_t newTemp = convertTemperatureSensor();

  // send to UART
  Serial1.print(TEMP_CHAR);
  Serial1.println(newTemp);
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

// --------------------------------------
// SENSOR CONVERSION METHODS
// --------------------------------------
// convert photocell reaidng
String convertPhototocellSensor() {
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 100) {
    return "Dark";

  } else if (photocellReading < 300) {
    return "Dim";

  } else if (photocellReading < 500) {
    return "Light";

  } else if (photocellReading < 900) {
    return "Bright";

  } else {
    return "Very bright!";
  }
}

// convert temperature reading
uint8_t convertTemperatureSensor() { 
  // converting that reading to voltage
  float voltage = tempReading * 5.0;
  voltage /= 1024.0; 
  
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                //to degrees ((voltage - 500mV) times 100)
  
  // convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  // change to int
  uint8_t returnTemp = (uint8_t) temperatureF;

  return returnTemp;
}

