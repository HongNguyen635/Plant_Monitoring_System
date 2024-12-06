//this is master
#include <TimerOne.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// components pins
#define displaySDA 20
#define displaySCL 21
#define pumpPin 7
#define buzzerPin 9

#define ledRed 5
#define ledBlue 6
#define ledGreen 4

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
#define WATER_LEVEL_CHAR 'J'
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

uint32_t counter = 0;

// components status
// pump
bool pumpOn = false;
uint32_t pumpStart = 0;

// led
bool isLedManual = false;
bool isLedOn = false;
char ledColor = 'A'; // A = RGB
bool isLedDim = false;
uint32_t ledRGBstart = 0;
char allColorCurrent = 'R';

// buzzer
bool isBuzzerOn = false;
uint32_t buzzerStart = 0;

// display
String messages [] = {"There are no gardening mistakes",
                      "What a beautiful plant =]",
                      "Ah ha ha ha, keep me alive, please"};
uint8_t msgIndex = 0;


uint16_t photocellReading = 0;
int tempReading = 0;
int moistureReading = 0;
int tempSoilReading = 0;
bool IR1Reading = 0;
bool IR2Reading = 0;
bool IR3Reading = 0;
bool IR4Reading = 0;
bool IR5Reading = 0;
bool smokeReading = 0;
bool flameReading = 0;
bool waterReading = 0;

int photocellPeriod = 0;
int tempPeriod = 0;
int moisturePeriod = 0;
int tempSoilPeriod = 0;
int IR1Period = 0;
int IR2Period = 0;
int IR3Period = 0;
int IR4Period = 0;
int IR5Period = 5;
int waterPeriod = 0;
int flamePeriod = 0;
int smokePeriod = 0;

bool readPhotocell = false;
bool readTemp = false;
bool readMoisture = false;
bool readTempSoil = false;
bool readIR1 = false;
bool readIR2 = false;
bool readIR3 = false;
bool readIR4 = false;
bool readIR5 = false;
bool readWater = false;
bool readFlame = false;
bool readSmoke = false;

// keep track of the total messages
uint32_t websiteCommandCount = 0;
uint32_t centralToPeripheralCount = 0;

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

  pinMode(buzzerPin, OUTPUT);

  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  pinMode(pumpPin, OUTPUT);
  // digitalWrite(pumpPin, LOW);

  // Serial.println("works");
  Timer1.initialize(1000000);
  // Serial.println("works");
  Timer1.attachInterrupt(sensorCheck);
}

// test communication to uno
void loop()
{
  // ----- ESP32 UART COM -----
  // receive cmd from esp32
  if (Serial1.available()) {
    // read in the char
    char cmd = Serial1.read();
    Serial.print("cmd: ");
    Serial.println(cmd);


    if (cmd == CONFIG_CHAR) {
      // save the update rate
      String tempRate = Serial1.readStringUntil('\n');
      String soilRate = Serial1.readStringUntil('\n');
      String photocellRate = Serial1.readStringUntil('\n');

      tempPeriod = tempRate.toInt();
      tempSoilPeriod = soilRate.toInt();
      photocellPeriod = photocellRate.toInt();

      // print config info
      Serial.println("New configurations:");
      Serial.print("Air temperature rate: ");
      Serial.println(tempRate);
      Serial.print("Moisture & soil temperature rate: ");
      Serial.println(soilRate);
      Serial.print("Photocell sensor rate: ");
      Serial.println(photocellRate);

      // increment the command count
      ++websiteCommandCount;
    }

    else if (cmd == TEMP_CHAR) {
      // ask for new data
      requestTemp();

      Serial.println("I'm here");

      // convert to human-readable
      String convertedTemp = String(convertTemperatureSensor());

      Serial1.print(TEMP_CHAR);
      Serial1.println(convertedTemp); // send to website

      // print report
      Serial.print("Temperature Sensor, raw reading: ");
      Serial.println(tempReading);
      Serial.println("Report mode: on-demand");

      ++websiteCommandCount;
    }

    else if (cmd == MOISTURE_CHAR) {
      requestMoisture();
      requestTempSoil();
      String newTempSoil = String(covertTempSoilSensor());
      String newMoisture = String(convertMoistureSensor());

      // send to esp32
      Serial1.print(MOISTURE_CHAR);
      Serial1.println(newMoisture);
      Serial1.println(newTempSoil);

      // print report
      Serial.print("Moisture Sensor, raw reading: ");
      Serial.println(moistureReading);
      Serial.print("Soil Temperature, raw reading: ");
      Serial.println(tempSoilReading);
      Serial.println("Report mode: on-demand");

      ++websiteCommandCount;
    }

    else if (cmd == PHOTOCELL_CHAR) {
      // read
      requestPhotocell();
      String photocellStatus = convertPhototocellSensor();

      // send to ESP32
      Serial1.print(PHOTOCELL_CHAR);
      Serial1.println(photocellStatus);

      // print report
      Serial.print("Photocell Sensor, raw reading: ");
      Serial.println(photocellReading);
      Serial.println("Report mode: on-demand");

      ++websiteCommandCount;
    }

    else if (cmd == WATER_CMD_CHAR) {
      // turn on the pump
      // noInterrupts();
      // digitalWrite(pumpPin, HIGH);
      // interrupts();
      // Serial.println("Hey");
      // pumpStart = millis();
      // pumpOn = true;
      BTSerial.write(WATER_CMD_CHAR);

      ++websiteCommandCount;
    }

    else if (cmd == TOGGLE_LED_CHAR) {
      // toggle the LED
      toggleLED();

      // also if you manually turn it on,
      // you need to manually turn it off
      if (isLedManual && !isLedOn) {
        isLedManual = false;
      } else if (isLedOn) {
        isLedManual = true;
      }

      ++websiteCommandCount;
    }

    else if (cmd == LED_BRIGHTNESS_CHAR) {
      toggleBrightness();

      ++websiteCommandCount;
    }

    else if (cmd == LED_RED_CHAR) {
      ledColor = 'R';
      
      if (isLedOn) {
        turnOnLED(); // switch color
      }

      ++websiteCommandCount;
    }

    else if (cmd == LED_BLUE_CHAR) {
      ledColor = 'B';
      
      if (isLedOn) {
        turnOnLED(); // switch color
      }

      ++websiteCommandCount;
    }

    else if (cmd == LED_GREEN_CHAR) {
      ledColor = 'G';
      
      if (isLedOn) {
        turnOnLED(); // switch color
      }

      ++websiteCommandCount;
    }

    else if (cmd == LED_RGB_CHAR) {
      ledColor = 'A';
      
      if (isLedOn) {
        turnOnLED(); // switch color
      }

      ++websiteCommandCount;
    }

    else if (cmd == BUZZER_CMD_CHAR) {
      tone(buzzerPin, 100);
      isBuzzerOn = true;
      buzzerStart = millis();

      ++websiteCommandCount;
    }

    else if (cmd == WRITE_DISPLAY_CHAR) {
      // choose a msg and write to the display
      lcd.clear();
      lcd.print(messages[msgIndex]);
      ++msgIndex;
      if (msgIndex == 3) {
        msgIndex = 0;
      }

      ++websiteCommandCount;
    }

    else if (cmd == CLEAR_DISPLAY_CHAR) {
      lcd.clear();

      ++websiteCommandCount;
    }
    

    Serial.print("\nTotal commands from website: ");
    Serial.println(websiteCommandCount);
    Serial.println();
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
    Serial.print("Photocell Sensor, raw reading: ");
    Serial.println(photocellReading);
    Serial.println("Report mode: periodical");
    readPhotocell = false;

    // sent to website
    String photocellStatus = convertPhototocellSensor();

    // send to ESP32
    Serial1.print(PHOTOCELL_CHAR);
    Serial1.println(photocellStatus);
  }
  if (readTemp) {
    requestTemp();
    Serial.print("Temperature Sensor, raw reading: ");
    Serial.println(tempReading);
    Serial.println("Report mode: periodical");
    readTemp = false;

    // convert to human-readable
    uint8_t convertedTemp = convertTemperatureSensor();

    Serial1.print(TEMP_CHAR);
    Serial1.print(convertedTemp); // send to website
  }
  // if (readMoisture) {
  //   requestMoisture();
  //   Serial.print("Moisture Sensor, raw reading: ");
  //   Serial.println(moistureReading);
  //   Serial.println("Report mode: periodical");
  //   readMoisture = false;
  // }
  if (readMoisture) {
  requestMoisture();
  Serial.print("Soil Moisture, raw reading: ");
  Serial.println(moistureReading);
  Serial.println("Report mode: periodical");
  readMoisture = false;

  uint8_t newTempSoil = covertTempSoilSensor();
  uint8_t newMoisture = convertMoistureSensor();

  // send to esp32
  Serial1.print(MOISTURE_CHAR);
  Serial1.print(newMoisture);
  Serial1.print(newTempSoil);
  }
  if (readTempSoil) {
    requestTempSoil();
    Serial.print("Soil Temperature, raw reading: ");
    Serial.println(tempSoilReading);
    Serial.println("Report mode: periodical");
    readTempSoil = false;

    uint8_t newTempSoil = covertTempSoilSensor();
    uint8_t newMoisture = convertMoistureSensor();

    // send to esp32
    Serial1.print(MOISTURE_CHAR);
    Serial1.print(newMoisture);
    Serial1.print(newTempSoil);
  }
  if (readIR1) {
    requestIR1();

    Serial1.print(INTRUSION_DETECTED_CHAR); // send to esp32

    if (IR1Reading) {
      Serial1.println("1");
    } else {
      Serial1.println("0");
    }

    // Serial1.print(IR1Reading);

    if (IR1Reading == true) {
      Serial.println("IR1: no object detected");
    } else {
      Serial.println("IR1: object detected");
    }
    readIR1 = false;
  }
  if (readIR2) {
    requestIR2();

    Serial1.print(INTRUSION_DETECTED_CHAR); // send to esp32
    
    if (IR2Reading) {
      Serial1.println("1");
    } else {
      Serial1.println("0");
    }

    if (IR2Reading == true) {
      Serial.println("IR2: no object detected");
    } else {
      Serial.println("IR2: object detected");
    }
    readIR2 = false;
  }
  if (readIR3) {
    requestIR3();

    Serial1.print(INTRUSION_DETECTED_CHAR); // send to esp32
  
    if (IR3Reading) {
      Serial1.println("1");
    } else {
      Serial1.println("0");
    }

    if (IR3Reading == true) {
      Serial.println("IR3: no object detected");
    } else {
      Serial.println("IR3: object detected");
    }
    readIR3 = false;
  }
  if (readIR4) {
    requestIR4();

    Serial1.print(INTRUSION_DETECTED_CHAR); // send to esp32
    
    if (IR4Reading) {
      Serial1.println("1");
    } else {
      Serial1.println("0");
    }

    if (IR4Reading == true) {
      Serial.println("IR4: no object detected");
    } else {
      Serial.println("IR4: object detected");
    }
    readIR4 = false;
  }
  if (readIR5) {
    requestIR5();

    Serial1.print(INTRUSION_DETECTED_CHAR); // send to esp32

    if (IR5Reading) {
      Serial1.println("1");
    } else {
      Serial1.println("0");
    }

    Serial1.print(IR5Reading);

    if (IR5Reading == true) {
      Serial.println("IR5: no object detected");
    } else {
      Serial.println("IR5: object detected");
    }
    readIR5 = false;
  }
  if (readWater) {
    requestWater();

    Serial1.print(WATER_LEVEL_CHAR);
    Serial1.println(waterReading);

    if (waterReading == false) {
      Serial.println("water is empty");
    } 
    readWater = false;
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

    Serial1.print(FLAME_SENSOR);
    Serial1.println(flameReading);

    if (flameReading == true) {
      Serial.println("flame detected");
    } else {
      Serial.println("no flame detected");
    }
    readFlame = false;
  }

  // pump
  // if moisture drop below 50%
  // if (moistureReading != 0 && moistureReading < 900) {
  //   pumpStart = millis();
  //   digitalWrite(pumpPin, HIGH);
  // }
  // if (pumpOn && ((millis() - pumpStart) >= 5000)) {
  //   pumpOn = false;
  //   digitalWrite(pumpPin, LOW);
  // }
  // if (pumpOn && (millis() - pumpStart > 2000)) {
  //   noInterrupts();
  //   digitalWrite(pumpPin, LOW);
  //   interrupts();
  //   pumpOn = false;
  // }

  // led
  if (photocellReading != 0 && photocellReading < 300) {
    // if the user manually turn it off, don't turn it on
    if (!isLedManual && !isLedOn) {
      turnOnLED();

      // send to esp32
      Serial1.print(TOGGLE_LED_CHAR);
      Serial1.println("1");

    }
  } else if (photocellReading >= 300) {
    // light, turn off
    // also, if user manually turn it on, don't turn
    // it off
    if (!isLedManual && isLedOn) {
      turnOffLED();

      // send to esp32
      Serial1.print(TOGGLE_LED_CHAR);
      Serial1.println("0");
    }
  }

  // if led on and is blinking rgb
  if (isLedOn && ledColor == 'A') {
    // check if 3s has passed
    if (millis() - ledRGBstart > 3000) {
      // switch to the next color & save the previous color
      uint8_t currentPin = ledBlue;
      switch (allColorCurrent) {
        case 'R':
          currentPin = ledBlue;
          allColorCurrent = ledGreen;
          break;

        case 'G':
          currentPin = ledGreen;
          allColorCurrent = ledBlue;
          break;

        case 'B':
          currentPin = ledBlue;
          allColorCurrent = ledRed;
          break;
      }

      // turn the next color on
      turnNextColor(currentPin, allColorCurrent);
    }
  }

  // buzzer
  if (isBuzzerOn && (millis() - buzzerStart > 2000)) {
    noTone(buzzerPin);
    isBuzzerOn = false;
  }
}

void sensorCheck(void) {
  counter++;
  if (photocellPeriod > 0 && counter % photocellPeriod == 0) {
    // requestPhotocell();
    readPhotocell = true;
  }
  if (tempPeriod > 0 && counter % tempPeriod == 0) {
    // requestTemp();
    readTemp = true;
  }
  if (moisturePeriod > 0 && counter % moisturePeriod == 0) {
    // requestMoisture();
    readMoisture = true;
  }
  if (tempSoilPeriod > 0 && counter % tempSoilPeriod == 0) {
    // requestTempSoil();
    readTempSoil = true;
  } 
  if (IR1Period > 0 && counter % IR1Period == 0) {
    readIR1 = true;
  }
  if (IR2Period > 0 && counter % IR2Period == 0) {
    readIR2 = true;
  }
  if (IR3Period > 0 && counter % IR3Period == 0) {
    readIR3 = true;
  }
  if (IR4Period > 0 && counter % IR4Period == 0) {
    readIR4 = true;
  }
  if (IR5Period > 0 && counter % IR5Period == 0) {
    readIR5 = true;
  }
  if (waterPeriod > 0 && counter % waterPeriod == 0) {
    readWater = true;
  }
  if (flamePeriod > 0 && counter % flamePeriod == 0) {
    readFlame = true;
  }
  if (smokePeriod > 0 && counter % smokePeriod == 0) {
  readSmoke = true;
  }
}


void requestPhotocell(void) {
  BTSerial.write(PHOTOCELL_CHAR);
  while (BTSerial.available() <  2) {}
  uint8_t hi = BTSerial.read();
  uint8_t lo = BTSerial.read();
  // Serial.println(hi);
  // Serial.println(lo);
  uint16_t BT = (hi << 8) | lo;
  // Serial.println(BT);
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

void requestWater() {
  BTSerial.write(WATER_LEVEL_CHAR);
  while (!BTSerial.available()) {}
  char BT = BTSerial.read();
  waterReading = (BT == 'H');
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
  while (!BTSerial.available()) {}
  int BT = BTSerial.read();
  moistureReading = BT;
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
int convertTemperatureSensor() { 
  // converting that reading to voltage
  float voltage = tempReading * 5.0;
  voltage /= 1024.0; 
  
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                //to degrees ((voltage - 500mV) times 100)
  
  // convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  // change to int
  int returnTemp = (int) temperatureF;

  return returnTemp;
}

// convert soil temperature sensor
uint8_t covertTempSoilSensor() {
  // convert to F
  float temperatureF = (tempReading * 9.0 / 5.0) + 32.0;

  // change to int
  uint8_t returnTemp = (uint8_t) temperatureF;

  return returnTemp;
}

// comvert moisture sensor
uint8_t convertMoistureSensor() {
  // uint8_t percentageHumididy  = map(moistureReading, 2000, 200, 100, 0);
  // return percentageHumididy;
  return -1;
}

// toggle the LED on or off
void toggleLED() {
  // if it's on, just turn off
  if (isLedOn) {
    turnOffLED();

    
  } else {
    turnOnLED();
  }
  // toggle the light
  isLedOn = !isLedOn;
}

// toggle the LED brightness
void toggleBrightness() {
  isLedDim = !isLedDim;
  // if LED is not on, return
  if (!isLedOn) return;

  // else change the light
  turnOnLED();
}

void turnOnLED() {
  // get the color to turn on
  uint8_t pinNumber = ledRed;

  switch (ledColor) {
    case 'B':
      pinNumber = ledBlue;
    break;

    case 'G':
      pinNumber = ledGreen;
    break;

    default:
    // red or all
    break;
  }

  // turn off everything first, and turn on
  // the correct color
  turnOffLED();

  // check the brightness setting
  if (isLedDim) {
    if (ledColor == 'A') {
      // turn on all
      analogWrite(ledRed, 10);
      analogWrite(ledBlue, 10);
      analogWrite(ledGreen, 10);
    } else {
      analogWrite(pinNumber, 10);
    }
  } else {
    if (ledColor == 'A') {
      // turn on all
      analogWrite(ledGreen, 1023);
      analogWrite(ledRed, 1023);
      analogWrite(ledBlue, 1023);
    } else {
      analogWrite(pinNumber, 1023);
    }
  }
}

void turnOffLED() {
  analogWrite(ledRed, 0);
  analogWrite(ledGreen, 0);
  analogWrite(ledBlue, 0);
}

// rotate RGB
void turnNextColor(uint8_t current, uint8_t next) {
  analogWrite(current, 0);
  
  // check the brightness setting
  if (isLedDim) {
    analogWrite(next, 10);
  } else {
    analogWrite(next, 1000);
  }
} 