/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  The methods used to control and monitor the DHT11 temperature sensor.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 *
 * Most of the code originally from:
 *
 * FILE: dht22.cpp
 * VERSION: 0.1.00
 * PURPOSE: DHT22 Temperature & Humidity Sensor library for Arduino
 * HISTORY:
 * 0.1.0 by Rob Tillaart (01/04/2011)
 * inspired by DHT11 library
 *
 */

#include <Arduino.h>
#include "Temperature.h"

const int TIMEOUT = 10000;

/**
 * Read the temperature and humidity. Returns true if the data was read, false otherwise
 */
bool Temperature::read() {
    int chk = read11(m_pin);
    switch (chk) {
        case  0: /* success */        break;
        case -1: /* Checksum error */ return false;
        case -2: /* Time out error */ return false;
        default: /* Unknown error  */ return false;
    }
    return true;
}


// return values:
//  0 : OK
// -1 : checksum error
// -2 : timeout
int Temperature::read11(uint8_t pin)
{
    // READ VALUES
    int rv = read(pin);
    if (rv != 0)
        return rv;

    // CONVERT AND STORE
    m_humidity    = m_bits[0]; // bit[1] == 0;
    m_temperature = m_bits[2]; // bits[3] == 0;

    // TEST CHECKSUM
    uint8_t sum = m_bits[0] + m_bits[2]; // bits[1] && bits[3] both 0
    if (m_bits[4] != sum)
        return -1;

    return 0;
}

// return values:
//  0 : OK
// -1 : checksum error
// -2 : timeout
int Temperature::read22(uint8_t pin)
{
    // READ VALUES
    int rv = read(pin);
    if (rv != 0)
        return rv;

    // CONVERT AND STORE
    m_humidity = word(m_bits[0], m_bits[1]) * 0.1;

    int sign = 1;
    if (m_bits[2] & 0x80) { // negative temperature
        m_bits[2] = m_bits[2] & 0x7F;
        sign = -1;
    }
    m_temperature = sign * word(m_bits[2], m_bits[3]) * 0.1;

    // TEST CHECKSUM
    uint8_t sum = m_bits[0] + m_bits[1] + m_bits[2] + m_bits[3];
    if (m_bits[4] != sum)
        return -1;

    return 0;
}

// return values:
//  0 : OK
// -2 : timeout
int Temperature::read(uint8_t pin)
{
    // INIT BUFFERVAR TO RECEIVE DATA
    uint8_t cnt = 7;
    uint8_t idx = 0;

    // EMPTY BUFFER
    for (int i = 0; i < 5; i++) {
        m_bits[i] = 0;
    }

    // REQUEST SAMPLE
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(20);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);

    // GET ACKNOWLEDGE or TIMEOUT
    unsigned int loopCnt = TIMEOUT;
    while (digitalRead(pin) == LOW)
        if (loopCnt-- == 0)
            return -2;

    loopCnt = TIMEOUT;
    while (digitalRead(pin) == HIGH)
        if (loopCnt-- == 0)
            return -2;

    // READ THE OUTPUT - 40 BITS => 5 BYTES
    for (int i = 0; i < 40; i++) {
        loopCnt = TIMEOUT;
        while (digitalRead(pin) == LOW)
            if (loopCnt-- == 0)
                return -2;

        unsigned long t = micros();

        loopCnt = TIMEOUT;
        while (digitalRead(pin) == HIGH)
            if (loopCnt-- == 0)
                return -2;

        if ((micros() - t) > 40)
            m_bits[idx] |= (1 << cnt);
        if (cnt == 0) { // next byte?
            cnt = 7;
            idx++;
        } else
            cnt--;
    }

    return 0;
}
