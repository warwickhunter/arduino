// 
// FILE:  dht_test.pde
//
// PURPOSE: DHT library test sketch for Arduino
//
// http://arduino.cc/playground/Main/DHTLib
//

#include <dht.h>

dht DHT;

#define DHT11_PIN 4 // Digital PIN 4

int sampleCount = 0;

void printHeader()
{
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)");
}

void setup()
{
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println(__DATE__ " " __TIME__);
  printHeader();
}

void loop()
{
  // READ DATA
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case 0:  Serial.print("OK\t"); break;
    case -1: Serial.print("Checksum error\t"); break;
    case -2: Serial.print("Time out error\t"); break;
    default: Serial.print("Unknown error\t"); break;
  }

  // DISPLAY DATA
  Serial.print(DHT.humidity,1);
  Serial.print("\t\t");
  Serial.println(DHT.temperature,1);

  ++sampleCount;
  if (sampleCount > 10) {
      printHeader();
      sampleCount = 0;
  }

  delay(1000);
}

