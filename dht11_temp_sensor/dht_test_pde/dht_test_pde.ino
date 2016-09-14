// 
// FILE:  dht_test.pde
//
// PURPOSE: DHT library test sketch for Arduino
//
// http://arduino.cc/playground/Main/DHTLib
//

#include <DHT_U.h>


#define DHT11_PIN 4 // Digital PIN 4

DHT dht(DHT11_PIN, DHT11);

int sampleCount = 0;

void printHeader()
{
  Serial.println();
  Serial.println("Humidity (%)\tTemperature (C)");
}

void setup()
{
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.println(__DATE__ " " __TIME__);
  printHeader();
  dht.begin();
}

void loop()
{
  // DISPLAY DATA
  Serial.print(dht.readHumidity(),1);
  Serial.print("\t\t");
  Serial.println(dht.readTemperature(),1);

  ++sampleCount;
  if (sampleCount > 20) {
      printHeader();
      sampleCount = 0;
  }

  delay(1000);
}

