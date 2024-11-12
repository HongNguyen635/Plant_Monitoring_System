//this is master

#include <SoftwareSerial.h>

// setup bluetooth
SoftwareSerial BTSerial(12, 2); // RX, TX

// set up the baud rate for bluetooth
void setup() 
{
  BTSerial.begin(38400);
}

// test communication to uno
void loop()
{
 BTSerial.write('1');
}
