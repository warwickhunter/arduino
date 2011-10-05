/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  The methods used to control and monitor the voltage divider.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */

#ifndef VOLTAGE_H_
#define VOLTAGE_H_

class Voltage {

public:
    explicit Voltage(int analoguePinNumber);

    void setup();
    bool read();

    double getVoltage();

private:
    // Scale the value of the sensor (0-1023) to be volts (0-25v)
    double toVolts(int sensorValue);

    int    m_pin;
    double m_voltage;
    int    m_sensorValue;
};

inline Voltage::Voltage(int analoguePinNumber)
    : m_pin(analoguePinNumber) {
}

inline void Voltage::setup() {
}

inline double Voltage::getVoltage() {
    return m_voltage;
}

#endif /* VOLTAGE_H_ */
