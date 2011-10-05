//    FILE: dht.h
// VERSION: 0.1.00
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//
//     URL: http://arduino.cc/playground/Main/DHTLib
//
// HISTORY:
// see dht.cpp file
// 

#ifndef dht_h
#define dht_h

#include <stdint.h>

class dht
{
  public:
    int read11(uint8_t pin);
    int read22(uint8_t pin);
    double humidity;
    double temperature;

  private:
    uint8_t bits[5];  // buffer to receive data
    int read(uint8_t pin);
};
#endif
//
// END OF FILE
//
