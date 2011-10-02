/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  The methods used to control and monitor the DHT11 temperature sensor.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */

#include "TemperatureSensor.h"
#include <WProgram.h>

TemperatureSensor::TemperatureSensor(int digitalPinNumber)
    : m_pin(digitalPinNumber), m_dht() {
}

TemperatureSensor::~TemperatureSensor() {
}

void TemperatureSensor::setup() {
}

/**
 * Read the temperature and humidity. Returns true if the data was read, false otherwise
 */
bool TemperatureSensor::read() {

    int chk = m_dht.read11(m_pin);
    switch (chk) {
        case  0: /* success */ break;
        case -1: Serial.println("Checksum error\t"); return false;
        case -2: Serial.println("Time out error\t"); return false;
        default: Serial.println("Unknown error\t"); return false;
    }
    return true;
}

double TemperatureSensor::getHumidity() {
    return m_dht.humidity;
}

double TemperatureSensor::getTemperature() {
    return m_dht.temperature;
}



