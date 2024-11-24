//this is slave
#include "Adafruit_seesaw.h"
#include <SoftwareSerial.h>

// sensors pins
#define photocellPin A0
#define temperaturePin A1
#define irSensor1 2
#define irSensor2 3
#define buzzerPin 5

// bluetooth communication char
#define PHOTOCELL_CHAR 'A'
#define TEMP_CHAR 'B'
#define MOISTURE_CHAR 'C'
#define TEMP_SOIL_CHAR 'D'
#define IR_SENSOR1 'E'
#define IR_SENSOR2 'F'

volatile bool objectPresentSensor1 = false;
bool objectPresentSensor2 = false;


SoftwareSerial BTSerial(10, 11); // RX, TX

// setup serial monitor and bluetooth
// also test the onboard LED
void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);


  // INPUT:
  //pinMode(irSensor1, INPUT); 
  pinMode(irSensor1, INPUT_PULLUP); 
  pinMode(irSensor2, INPUT); 

  pinMode(photocellPin, INPUT);
  pinMode(temperaturePin, INPUT);

  ss.begin(0x36);
  // OUTPUT
  pinMode(buzzerPin, OUTPUT);

  // IR sensor
  attachInterrupt(digitalPinToInterrupt(irSensor1), irSensor1_ISR, FALLING); 
  attachInterrupt(digitalPinToInterrupt(irSensor2), irSensor2_ISR, FALLING); 

}

// test bluetooth to read msg from mega
void loop() 
{
  // TODO: uncomment later
  // if (BTSerial.available()) {
  //   Serial.println(BTSerial.read() - '0');
  // }


  if (objectPresentSensor1) {
    if (digitalRead(irSensor1) == LOW) {
      Serial.println("object");

          // buzzer
          tone(buzzerPin, 100);
          delay(1000);
          noTone(buzzerPin); 
    }
    else {
        Serial.println("false alarm");
    }
    
          objectPresentSensor1 = false;
    // reattch to interrupt to detect object after beeps
    //attachInterrupt(digitalPinToInterrupt(irSensor1), irSensor1_ISR, FALLING); 
  }
  else {
    Serial.println("no object");
  }

  if (objectPresentSensor2) {
  Serial.println("object");
  objectPresentSensor2 = false;

  // buzzer
  tone(buzzerPin, 100);
  delay(1000);
  noTone(buzzerPin); 


  // reattch to interrupt to detect object after beeps
  attachInterrupt(digitalPinToInterrupt(irSensor2), irSensor2_ISR, FALLING); 
  }

  Serial.println(digitalRead(irSensor1));

  // ------------ TODO: FIX ABOVE CODE LATER ----------


  // ---------- Bluetooth Reading ------------
  if (BTSerial.available()) {
    // reads the command char
    char BT = BTSerial.read();
    // if statement chunk, sends sensor data depending on
    // command char BT
    if (BT == PHOTOCELL_CHAR) {
      // data send protocol for the photocell resistor
      uint16_t photocell = analogRead(photocellPin);
      uint8_t hi = photocell >> 8;
      uint8_t lo = photocell & 0xFF;
      // send first byte
      BTSerial.write(hi);
      // wait for ack
      while (!BTSerial.available()) {}
      // send second byte
      BTSerial.write(lo);
    } else if (BT == TEMP_CHAR) {
      // data send protocol for the temperature sensor
      BTSerial.write(analogRead(temperaturePin));
    } else if (BT == MOISTURE_CHAR) {
      // data send protocol for the moisture sensor
      BTSerial.write(MOISTURE_CHAR);
    } else if (BT == TEMP_SOIL_CHAR) {
      // data send protocol for the temperature sensor
      // attached to the moisture sensor
      BTSerial.write(TEMP_SOIL_CHAR);
    } else if (BT == IR_SENSOR1) {
      // data send protocol for the first IR sensor
      // sends H or L for high or low
      if (digitalRead(irSensor1) == HIGH) {
        BTSerial.write('H');
      } else {
        BTSerial.write('L');
      }
    } else if (BT == IR_SENSOR2) {
      // data send protocol for the second IR sensor
      // sends H or L for high or low
      if (digitalRead(irSensor2) == HIGH) {
        BTSerial.write('H');
      } else {
        BTSerial.write('L');
      }
    } else {
      // command char not recognized, do nothing
      Serial.println("char not recognized");
    }
  }
}


// --------------------------------------
// SENSOR READING METHODS
// --------------------------------------

// get the photocell reading
String getPhototocellSensor() {
  // get the raw photocell reading
  int photocellReading = analogRead(photocellPin);  
  Serial.println(photocellReading);
 
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

// get temperature reading
float getTemperatureSensor() {
  int reading = analogRead(temperaturePin);  
 
  // converting that reading to voltage
  float voltage = reading * 5.0;
  voltage /= 1024.0; 
  
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                //to degrees ((voltage - 500mV) times 100)
  
  // convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  return temperatureF;
}


// IR sensors ISR
void irSensor1_ISR() {
  //detachInterrupt(digitalPinToInterrupt(irSensor1_ISR)); 
  objectPresentSensor1 = true;
}

void irSensor2_ISR() {
  detachInterrupt(digitalPinToInterrupt(irSensor2_ISR)); 
  objectPresentSensor2 = true;
}


// --------------------------------------
// UTILITY METHODS
// --------------------------------------

