/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  The methods used to control and monitor the DHT11 temperature sensor.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */

#include <Arduino.h>
#include "Temperature.h"

/**
 * Read the temperature and humidity. Returns true if the data was read, false otherwise
 */
bool Temperature::read() {

    int chk = m_dht.read11(m_pin);
    switch (chk) {
        case  0: /* success */ break;
        case -1: Serial.println("Checksum error"); return false;
        case -2: Serial.println("Time out error"); return false;
        default: Serial.println("Unknown error"); return false;
    }
    return true;
}
