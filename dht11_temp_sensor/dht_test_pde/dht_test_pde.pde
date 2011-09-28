// 
//   FILE:  dht_test.pde
// PURPOSE: DHT library test sketch for Arduino
//

#include <dht.h>

dht DHT;

#define DHT11_PIN 4
#define DHT22_PIN 5

void setup()
{
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop()
{
  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case 0:  Serial.print("OK,\t"); break;
    case -1: Serial.print("Checksum error,\t"); break;
    case -2: Serial.print("Time out error,\t"); break;
    default: Serial.print("Unknown error,\t"); break;
  }
 // DISPLAY DATA
  Serial.print(DHT.humidity,1);
  Serial.print(",\t\t");
  Serial.println(DHT.temperature,1);

  delay(1000);
}
//
// END OF FILE
//
