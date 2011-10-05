/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  The methods used to control and monitor the DHT11 temperature sensor.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 *
 * Some code originally from:
 * FILE: dht.h
 * VERSION: 0.1.00
 * PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
 * URL: http://arduino.cc/playground/Main/DHTLib
 */

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include <stdint.h>

class Temperature {
public:
    explicit Temperature(uint8_t digitalPinNumber);

    void setup();

    /**
     * Read the temperature and humidity from the sensor. Returns true if the data was read, false otherwise
     */
    bool read();

    double getHumidity();
    double getTemperature();

private:
    int read11(uint8_t pin);
    int read22(uint8_t pin);
    int read(uint8_t pin);

    uint8_t m_pin;
    uint8_t m_bits[5];  // buffer to receive data
    double  m_humidity;
    double  m_temperature;
};

inline Temperature::Temperature(uint8_t digitalPinNumber)
  : m_pin(digitalPinNumber) {
}

inline void Temperature::setup() {
}

inline double Temperature::getHumidity() {
    return m_humidity;
}

inline double Temperature::getTemperature() {
    return m_temperature;
}

#endif /* TEMPERATURE_H_ */
