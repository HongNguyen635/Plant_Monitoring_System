// Credit: thanks to Kris Kasprzak (YouTube) for providing
// tutorial on how to set up website using the ESP32

#include <WiFi.h>      
#include <WebServer.h> 
#include "Dashboard.h" // stores the html page code

// post web pages to home intranet for easy debugging
// just need to refresh the browser as apposed to reconnection
// to the web server
#define USE_INTRANET // comment this line out when go live

// test with home wifi
#define LOCAL_SSID "wifi_name"
#define LOCAL_PASS "wifi_pass"

// once read to go live these settings are what the client will connect to
// (name & pass of the access point)
#define AP_SSID "PlantMonitoringDashboard"
#define AP_PASS "1234567890"

// TODO: define the arduino pins for communication
#define ESP32LED 2
bool currentState = false;

// stores raw sensors and components data
uint16_t photocellSensor = 0;
uint16_t airTemperatureSensor = 0;
bool irSensor1 = false; // false = no object
bool irSensor2 = false; // false = no object

// TODO: add moisture sensor and soil temp

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
  // setup the serial monitor
  Serial.begin(9600);

  pinMode(ESP32LED, OUTPUT);
  digitalWrite(ESP32LED, LOW);


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

  printWifiStatus();


  // these calls will handle data coming back from the web page
  // this one is a page request, upon ESP getting / string 
  // the web page will be sent
  server.on("/", SendWebsite);

  // upon esp getting /XML string, ESP will build and send the XML, 
  // this is how we refresh just parts of the web page
  server.on("/xml", SendXML);

  // TODO: add server.on statement for each button on the website

  // test button to turn on ESP32 LED
  server.on("/esp32_led_button", updateESP32LED);

  server.on("/config", updateConfig);
  server.on("/airTempBtn", updateAirTemp);
  server.on("/soilBtn", updateSoil);
  server.on("/photocellBtn", updatePhotocell);
  server.on("/irBtn", updateIR);
  server.on("/waterBtn", waterPlant);
  server.on("/growLightBtn", growLightBtn);
  

  // finally begin the server
  server.begin();

}

void loop() {
  // TODO: add logic to get sensor from mega.

  // call this repeatedly or the web page won't get instructions
  // to do things
  server.handleClient();
}


// ------- HTTP Request Handler -------

void updateESP32LED() {
  currentState = !currentState;

  digitalWrite(ESP32LED, currentState);
  Serial.println(currentState);

  // option 1: send no information back, but at least keep the page live
  // just send nothing back
  server.send(200, "text/plain", ""); //Send web page

  // option 2: send something back immediately, maybe a pass/fail indication, maybe a measured value
  // here is how you send data back immediately and NOT through the general XML page update code
  // my simple example guesses at fan speed--ideally measure it and send back real data
  // i avoid strings at all caost, hence all the code to start with "" in the buffer and build a
  // simple piece of data
  // FanRPM = map(FanSpeed, 0, 255, 0, 2400);
  // strcpy(buf, "");
  // sprintf(buf, "%d", FanRPM);
  // sprintf(buf, buf);

  // // now send it back
  // server.send(200, "text/plain", buf); //Send web page
}

// TODO: complete the following methods
void updateConfig() {

}

void updateAirTemp() {

}

void updateSoil() {

}

void updatePhotocell() {

}

void updateIR() {

}

void waterPlant() {

}

void growLightBtn() {
  
}


// code to send the main web page
// PAGE_MAIN is a large char defined in Dashboard.h
void SendWebsite() {

  Serial.println("sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/html", PAGE_MAIN);

}

// code to send the main web page
// I avoid string data types at all cost hence all the char mainipulation code
void SendXML() {

  // Serial.println("sending xml");

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  // show led0 status
  if (currentState) {
    strcat(XML, "<LED>1</LED>\n");
  }
  else {
    strcat(XML, "<LED>0</LED>\n");
  }

  strcat(XML, "</Data>\n");

  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  //Serial.println(XML);

  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/xml", XML);
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