/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  The methods used to control and monitor the DHT11 temperature sensor.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include "dht.h"

class Temperature {

public:
    explicit Temperature(int digitalPinNumber);
    virtual ~Temperature();

    void setup();

    /**
     * Read the temperature and humidity from the sensor. Returns true if the data was read, false otherwise
     */
    bool read();

    double getHumidity();
    double getTemperature();

private:
    int m_pin;
    dht m_dht;
};


#endif /* TEMPERATURE_H_ */
