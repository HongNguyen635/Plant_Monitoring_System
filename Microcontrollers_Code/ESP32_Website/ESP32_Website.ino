// Credit: thanks to Kris Kasprzak (YouTube) for providing
// tutorial on how to set up website using the ESP32

#include <WiFi.h>      
#include <WebServer.h> 
#include "Dashboard.h" // stores the html page code
#include "HardwareSerial.h"

// post web pages to home intranet for easy debugging
// just need to refresh the browser as apposed to reconnection
// to the web server
#define USE_INTRANET // comment this line out when go live

// test with home wifi
#define LOCAL_SSID "Wifi_ID"
#define LOCAL_PASS "Wifi_pass"

// once read to go live these settings are what the client will connect to
// (name & pass of the access point)
#define AP_SSID "PlantMonitoringDashboard"
#define AP_PASS "5647382910"

// TODO: define the arduino pins for communication
#define RX2 16
#define TX2 17

HardwareSerial espSerial(2); // use UART2

// UART com char
#define PHOTOCELL_CHAR 'A'
#define TEMP_CHAR 'B'
#define MOISTURE_CHAR 'C'
#define TEMP_SOIL_CHAR 'D'
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

// stores raw sensors and components data
bool isIntrusionDetected = false;
bool isSmokeDetected = false;
bool isFlameDetected = false;
bool waterLevel = false; // true = full, false = empty
String airTempSensor = "0";
String moistureSensor = "0";
String soilTempSensor = "0";
uint8_t countSoundSensor = 0;
String humiditySensor = "0";
String photocellSensor = "Dark";
String ledColor = "RGB";

// TODO: add moisture sensor and soil temp
bool isLightOn = false; // LED grow light
bool isLightDim = false; // LED brightness

// XML size
char XML[2048]; // TODO: fix this to the actual website char size

// buffer holder for char operations
char buf[32];

// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;

// definitions of your desired intranet created by the ESP32
IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

// gotta create a server
WebServer server(80);

void setup() {
  Serial.begin(9600); // serial monitor
  espSerial.begin(9600, SERIAL_8N1, RX2, TX2); // UART

  Serial.println("Hey");


  // when web page are large, might not get a call back from the webpage
  // and the ESP thinks that something has locked up and will lock up
  // and reboot the ESP. So disable watchdog timer 0
  // disableCore0WDT();

  // maybe disable watch dog timer 1 if needed
  // disableCore1WDT();

  Serial.println("Starting Server!");

  // have the #define USE_INTRANET = connect to your home intranet, 
  // makes debugging easier
#ifdef USE_INTRANET
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();
#endif

  // if don't have #define USE_INTRANET, code below creates an access point
  // an intranet with no internet connection. But Clients can connect to 
  // your intranet and see the web page we are about to serve up
#ifndef USE_INTRANET
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  Actual_IP = WiFi.softAPIP();
  Serial.print("IP address: "); Serial.println(Actual_IP);
#endif

  Serial.println("Before");
  printWifiStatus();


  // these calls will handle data coming back from the web page
  // this one is a page request, upon ESP getting / string 
  // the web page will be sent
  server.on("/", SendWebsite);

  // upon esp getting /XML string, ESP will build and send the XML, 
  // this is how we refresh just parts of the web page
  server.on("/xml", SendXML);

  // TODO: add server.on statement for each button on the website
  server.on("/config", updateConfig);
  server.on("/airTempBtn", updateAirTemp);
  server.on("/soilBtn", updateSoil);
  server.on("/photocellBtn", updatePhotocell);
  server.on("/waterBtn", waterPlant);
  server.on("/growLightBtn", growLightBtn);
  server.on("/brightnessBtn", brightnessBtn);
  server.on("/redBtn", redBtn);
  server.on("/greenBtn", greenBtn);
  server.on("/blueBtn", blueBtn);
  server.on("/rgbBtn", rgbBtn);
  server.on("/buzzerBtn", buzzerBtn);
  server.on("/writeBtn", writeBtn);
  server.on("/clearBtn", clearBtn);
  

  // finally begin the server
  server.begin();

}

void loop() {
  // read 1 at a time, update, repeat
  
  // if there is data available via UART
  if (espSerial.available()) {
    // read in the character & process
    char cmd = espSerial.read();

    // Serial.println(cmd);

    
    if (cmd == PHOTOCELL_CHAR) {
      photocellSensor = espSerial.readStringUntil('\n');
      photocellSensor.trim();
    }

    else if (cmd == TEMP_CHAR) {
      airTempSensor = espSerial.readStringUntil('\n');
      airTempSensor.trim();
    }

    else if (cmd == MOISTURE_CHAR) {
      moistureSensor = espSerial.readStringUntil('\n');
      soilTempSensor = espSerial.readStringUntil('\n');

      moistureSensor.trim();
      soilTempSensor.trim();

      Serial.print("moisture: ");
      Serial.println(moistureSensor);
      Serial.print("soil temp: ");
      Serial.println(soilTempSensor);
    }

    else if (cmd == INTRUSION_DETECTED_CHAR) {
      String reading = espSerial.readStringUntil('\n');
      reading.trim();

      isIntrusionDetected = reading.toInt();
      
      Serial.println(isIntrusionDetected);
    }

    else if (cmd == WATER_LEVEL_CHAR) {
      String reading = espSerial.readStringUntil('\n');
      reading.trim();

      Serial.println("Here, water reading: ");
      Serial.println(waterLevel);
      
      waterLevel = reading.toInt();
    }

    else if (cmd == HUMIDITY_CHAR) {
      humiditySensor = espSerial.readStringUntil('\n');
      humiditySensor.trim();
    }

    else if (cmd == SOUND_SENSOR) {
      ++countSoundSensor;
    }

    else if (cmd == SMOKE_SENSOR) {
      String reading = espSerial.readStringUntil('\n');
      reading.trim();

      isSmokeDetected = reading.toInt();
    }

    else if (cmd == FLAME_SENSOR) {
      String reading = espSerial.readStringUntil('\n');
      reading.trim();
      
      isFlameDetected = reading.toInt();
    }

    else if (cmd == TOGGLE_LED_CHAR) {
      String reading = espSerial.readStringUntil('\n');
      reading.trim();

      

      isLightOn = reading.toInt();

      Serial.println("uslightom");
      Serial.println(isLightOn);
    }

    // else if (cmd == LED_BRIGHTNESS_CHAR) {
    //   String reading = espSerial.readStringUntil('\n');
    //   reading.trim();

    //   isLightDim = reading.toInt();
    // }

    else if (cmd == LED_RGB_CHAR) {
      ledColor = espSerial.readStringUntil('\n');
      ledColor.trim();
    }
    
  }

  // call this repeatedly or the web page won't get instructions
  // to do things
  server.handleClient();
}


// ------- HTTP Request Handler -------

// TODO: complete the following methods
void updateConfig() {
  // get all the configs
  String tempRate = server.arg("airTempRate");
  String soilRate = server.arg("soilRate");
  String photocellRate = server.arg("photocellRate");

  // send to central
  espSerial.print(CONFIG_CHAR);
  espSerial.println(tempRate);
  espSerial.println(soilRate);
  espSerial.println(photocellRate);

  // send no information back, but at least keep the page live
  // just send nothing back
  server.send(200, "text/plain", "");
}

void updateAirTemp() {
  // ask and wait for data
  espSerial.print(TEMP_CHAR);

  // discard any send in progress byte
  // and priortize this
  while(!espSerial.available()) {}

  char cmd = '?';
  do {
    cmd = espSerial.read();
  } while (cmd != TEMP_CHAR);

  airTempSensor = espSerial.readStringUntil('\n');
  airTempSensor.trim();
  Serial.println(airTempSensor);
  
  strcpy(buf, "");
  sprintf(buf, "%s", airTempSensor);
  server.send(200, "text/plain", buf);
}

void updateSoil() {
  espSerial.print(MOISTURE_CHAR);

  // discard any send in progress byte
  // and priortize this
  while(!espSerial.available()) {}
  
  char cmd = '?';
  do {
    cmd = espSerial.read();
  } while (cmd != MOISTURE_CHAR);

  moistureSensor = espSerial.readStringUntil('\n');
  soilTempSensor = espSerial.readStringUntil('\n');

  moistureSensor.trim();
  soilTempSensor.trim();

  Serial.print("moisture: ");
  Serial.println(moistureSensor);
  Serial.print("soil temp: ");
  Serial.println(soilTempSensor);

  // Prepare XML response
  String xmlResponse = "<data>";
  xmlResponse += "<moisture>" + moistureSensor + "</moisture>";
  xmlResponse += "<temp>" + soilTempSensor + "</temp>";
  xmlResponse += "</data>";
  
  server.send(200, "text/xml", xmlResponse);
}

void updatePhotocell() {
  espSerial.print(PHOTOCELL_CHAR);

  // discard any send in progress byte
  // and priortize this
  while(!espSerial.available()) {}

  char cmd = '?';
  do {
    cmd = espSerial.read();
  } while (cmd != PHOTOCELL_CHAR);

  photocellSensor = espSerial.readStringUntil('\n');
  photocellSensor.trim(); // trim white space
  
  strcpy(buf, "");
  sprintf(buf, "%s", photocellSensor);
  server.send(200, "text/plain", buf);
}

void waterPlant() {
  espSerial.print(WATER_CMD_CHAR);
  server.send(200, "text/plain", buf);
}

void growLightBtn() {
  // toggle LED
  isLightOn = !isLightOn;
  espSerial.print(TOGGLE_LED_CHAR);
  espSerial.print(isLightOn);

  // send status to server
  strcpy(buf, ""); // clear buffer

  if (isLightOn) {
    sprintf(buf, "%s", "On");
  } else {
    sprintf(buf, "%s", "Off");
  }
  server.send(200, "text/plain", buf);
}

void brightnessBtn() {
  // toggle dim/bright
  isLightDim = !isLightDim;
  espSerial.print(LED_BRIGHTNESS_CHAR);
  espSerial.print(isLightDim);
  
  // send status to server
  strcpy(buf, ""); // clear buffer

  if (isLightDim) {
    sprintf(buf, "%s", "Dim");
  } else {
    sprintf(buf, "%s", "Bright");
  }
  server.send(200, "text/plain", buf);
}

void redBtn() {
  ledColor = "Red";
  espSerial.print(LED_RED_CHAR);
  server.send(200, "text/plain", buf);
}

void greenBtn() {
  ledColor = "Green";
  espSerial.print(LED_GREEN_CHAR);
  server.send(200, "text/plain", buf);
}

void blueBtn() {
  ledColor = "Blue";
  espSerial.print(LED_BLUE_CHAR);
  server.send(200, "text/plain", buf);
}

void rgbBtn() {
  ledColor = "RGB";
  espSerial.print(LED_RGB_CHAR);
  server.send(200, "text/plain", buf);
}

void buzzerBtn() {
  espSerial.print(BUZZER_CMD_CHAR);
  server.send(200, "text/plain", buf);
}

void writeBtn() {
  espSerial.print(WRITE_DISPLAY_CHAR);
  server.send(200, "text/plain", buf);
}

void clearBtn() {
  espSerial.print(CLEAR_DISPLAY_CHAR);
  server.send(200, "text/plain", buf);
}


// code to send the main web page
// PAGE_MAIN is a large char defined in Dashboard.h
void SendWebsite() {

  Serial.println("sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(2000, "text/html", PAGE_MAIN);

}

// code to send the main web page
// I avoid string data types at all cost hence all the char mainipulation code
void SendXML() {

  // Serial.println("sending xml");

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  // send air temp
  sprintf(buf, "<AT>%s</AT>\n", airTempSensor);
  strcat(XML, buf);

  // send moisture
  sprintf(buf, "<M>%s</M>\n", moistureSensor);
  strcat(XML, buf);

  // send soil temp
  sprintf(buf, "<ST>%s</ST>\n", soilTempSensor);
  strcat(XML, buf);

  // send photocell
  sprintf(buf, "<P>%s</P>\n", photocellSensor);
  strcat(XML, buf);

  // send IR
  sprintf(buf, "<IR>%d</IR>\n", isIntrusionDetected ? 1 : 0);
  strcat(XML, buf);

  Serial.println("IR in xml");
  Serial.println(isIntrusionDetected);

  // send water level
  sprintf(buf, "<WL>%s</WL>\n", waterLevel ? "Ok" : "Empty");
  strcat(XML, buf);

  // send humidity
  sprintf(buf, "<H>%s</H>\n", humiditySensor);
  strcat(XML, buf);

  // send sound
  sprintf(buf, "<S>%d</S>\n", countSoundSensor);
  strcat(XML, buf);

  // send smoke
  sprintf(buf, "<SK>%d</SK>\n", isSmokeDetected ? 1 : 0);
  strcat(XML, buf);

  // send flame
  sprintf(buf, "<F>%d</F>\n", isFlameDetected ? 1 : 0);
  strcat(XML, buf);

  // send led status
  sprintf(buf, "<LED>%d</LED>\n", isLightOn ? 1 : 0);
  strcat(XML, buf);

  // send led brightness
  sprintf(buf, "<BRI>%d</BRI>\n", isLightDim ? 1 : 0);
  strcat(XML, buf);

  // send led color
  sprintf(buf, "<CO>%s</CO>\n", ledColor);
  strcat(XML, buf);

  strcat(XML, "</Data>\n");
  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  // Serial.println(XML);

  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(2000, "text/xml", XML);
}

// print the current wifi status
void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}