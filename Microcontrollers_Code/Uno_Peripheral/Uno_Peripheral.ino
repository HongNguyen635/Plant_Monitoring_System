//this is slave
#include <Adafruit_seesaw.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_PM25AQI.h>

// sensors pins
#define photocellPin A0
#define temperaturePin A1
#define irSensor1 2
#define irSensor2 3
#define irSensor3 6
#define irSensor4 7
#define irSensor5 8
#define buzzerPin 5
#define humidityPin 18
#define waterSensor A15
#define flamePin A2

// bluetooth communication char
#define PHOTOCELL_CHAR 'A'
#define TEMP_CHAR 'B'
#define MOISTURE_CHAR 'C'
#define TEMP_SOIL_CHAR 'D'
#define IR_SENSOR1 'E'
#define IR_SENSOR2 'F'
#define IR_SENSOR3 'G'
#define IR_SENSOR4 'H'
#define IR_SENSOR5 'Z'
#define WATER_LEVEL_CHAR 'J'
#define HUMIDITY_CHAR 'K'
#define SOUND_SENSOR 'L'
#define SMOKE_SENSOR 'M'
#define FLAME_SENSOR 'N'

#define DHTTYPE DHT11

Adafruit_PM25AQI aqi = Adafruit_PM25AQI();

volatile bool objectPresentSensor1 = false;
bool objectPresentSensor2 = false;

DHT dht(humidityPin, DHTTYPE);
Adafruit_seesaw ss;
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
  pinMode(irSensor3, INPUT);
  pinMode(irSensor4, INPUT);
  pinMode(irSensor5, INPUT);
  pinMode(photocellPin, INPUT);
  pinMode(temperaturePin, INPUT);
  pinMode(humidityPin, INPUT);
  pinMode(waterSensor, INPUT);
  pinMode(flamePin, INPUT);

  ss.begin(0x36);
  aqi.begin_I2C();
  // OUTPUT
  pinMode(buzzerPin, OUTPUT);

  // IR sensor
  // attachInterrupt(digitalPinToInterrupt(irSensor1), irSensor1_ISR, FALLING); 
  // attachInterrupt(digitalPinToInterrupt(irSensor2), irSensor2_ISR, FALLING); 

}

// test bluetooth to read msg from mega
void loop() 
{
  if (!digitalRead(irSensor1) || !digitalRead(irSensor2) || !digitalRead(irSensor3) || !digitalRead(irSensor4) || !digitalRead(irSensor5)) {
    tone(buzzerPin, 100);
  } else {
    noTone(buzzerPin);
  }
  PM25_AQI_Data data;
  // TODO: uncomment later
  // if (BTSerial.available()) {
  //   Serial.println(BTSerial.read() - '0');
  // }


  // if (objectPresentSensor1) {
  //   if (digitalRead(irSensor1) == LOW) {
  //     Serial.println("object");

  //         // buzzer
  //         tone(buzzerPin, 100);
  //         delay(1000);
  //         noTone(buzzerPin); 
  //   }
  //   else {
  //       Serial.println("false alarm");
  //   }
    
  //         objectPresentSensor1 = false;
  //   // reattch to interrupt to detect object after beeps
  //   //attachInterrupt(digitalPinToInterrupt(irSensor1), irSensor1_ISR, FALLING); 
  // }
  // else {
  //   Serial.println("no object");
  // }

  // if (objectPresentSensor2) {
  // Serial.println("object");
  // objectPresentSensor2 = false;

  // // buzzer
  // tone(buzzerPin, 100);
  // delay(1000);
  // noTone(buzzerPin); 


  // // reattch to interrupt to detect object after beeps
  // attachInterrupt(digitalPinToInterrupt(irSensor2), irSensor2_ISR, FALLING); 
  // }

  // Serial.println(digitalRead(irSensor1));

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
      // while (!BTSerial.available()) {}
      // send second byte
      BTSerial.write(lo);
    } else if (BT == TEMP_CHAR) {
      // data send protocol for the temperature sensor
      uint8_t tempReading = analogRead(temperaturePin);
      BTSerial.write(tempReading);
    } else if (BT == MOISTURE_CHAR) {
      // data send protocol for the photocell resistor
      uint16_t moisture = ss.touchRead(0);
      uint8_t hi = moisture >> 8;
      uint8_t lo = moisture & 0xFF;
      // send first byte
      BTSerial.write(hi);
      // wait for ack
      // while (!BTSerial.available()) {}
      // send second byte
      BTSerial.write(lo);
    } else if (BT == TEMP_SOIL_CHAR) {
      // data send protocol for the temperature sensor
      // attached to the moisture sensor
      uint8_t tempSoilReading = ss.getTemp();
      BTSerial.write(tempSoilReading);
    } else if (BT == IR_SENSOR1) {
      // data send protocol for the first IR sensor
      // sends H or L for high or low
      if (digitalRead(irSensor1) == LOW) {
        BTSerial.write('H');
      } else {
        BTSerial.write('L');
      }
    } else if (BT == IR_SENSOR2) {
      // data send protocol for the second IR sensor
      // sends H or L for high or low
      if (digitalRead(irSensor2) == LOW) {
        BTSerial.write('H');
      } else {
        BTSerial.write('L');
      }
    } else if (BT == IR_SENSOR3) {
      // data send protocol for the third IR sensor
      // sends H or L for high or low
      if (digitalRead(irSensor3) == LOW) {
        BTSerial.write('H');
      } else {
        BTSerial.write('L');
      }
    } else if (BT == IR_SENSOR4) {
      // data send protocol for the fourth IR sensor
      // sends H or L for high or low
      if (digitalRead(irSensor4) == LOW) {
        BTSerial.write('H');
      } else {
        BTSerial.write('L');
      }
    } else if (BT == IR_SENSOR5) {
      // data send protocol for the fourth IR sensor
      // sends H or L for high or low
      if (digitalRead(irSensor5) == LOW) {
        BTSerial.write('H');
      } else {
        BTSerial.write('L');
      }
    } else if (BT == HUMIDITY_CHAR) {
      uint16_t humidityReading = dht.readHumidity();
      uint8_t hi = humidityReading >> 8;
      uint8_t lo = humidityReading & 0xFF;
      BTSerial.write(hi);
      BTSerial.write(lo);
      
    } 
    // else if (BT == SMOKE_SENSOR) {
    //   // data send protocol for the fourth IR sensor
    //   // sends H or L for high or low
    //   if (digitalRead(smokePin) == HIGH) {
    //     BTSerial.write('H');
    //   } else {
    //     BTSerial.write('L');
    //   }
    // } 
    else if (BT == FLAME_SENSOR) {
      // data send protocol for the fourth IR sensor
      // sends H or L for high or low
      int sensorReading  = analogRead(flamePin);
      // map the sensor range (four options):
	    int range = map(sensorReading,  0, 1024, 0, 3);
      if (range == 0) {
        BTSerial.write('H');
      } else {
        BTSerial.write('L');
      }
    } else if (BT == WATER_LEVEL_CHAR) {
      int sensorReading = analogRead(waterSensor);
      if (sensorReading < 10) {
        BTSerial.write('L');
      } else {
        BTSerial.write('H');
      }
      }
    } else {
      // command char not recognized, do nothing
      // Serial.println("char not recognized");
    }
}



// IR sensors ISR
// void irSensor1_ISR() {
//   //detachInterrupt(digitalPinToInterrupt(irSensor1_ISR)); 
//   objectPresentSensor1 = true;
// }

// void irSensor2_ISR() {
//   // detachInterrupt(digitalPinToInterrupt(irSensor2_ISR)); 
//   objectPresentSensor2 = true;
// }