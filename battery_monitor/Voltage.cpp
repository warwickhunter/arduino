/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  The methods used to control and monitor the voltage divider.
 *
 *  Reads an analog input pin and then calibrates the value. The calibration is
 *  based on emperical measurements of the voltage divider using a multimeter. The
 *  voltage divider reduces the input voltage to one fifth of the input value.
 *
 *  Calibration of the voltage divider. The divisor appears to be 5.1005.
 *
 *                    0.00v == sensor 0    ouptut == 0
 *  9.13v / 5.1005 == 1.79v == sensor 384  output == 95
 *                    3.28v == sensor 705  output == 175
 *                    4.78v == sensor 1023 output == 255
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */

#include "Voltage.h"
#include <Arduino.h>

// The scaling factor that converts the sensor reading to a voltage. This has been calibrated
// with a volt meter and compensates for some inaccuracy in the voltage divider.
const double VOLTS_SCALE = 1051.47 / 25.0;

// Scale the value of the sensor (0-1023) to be volts (0-25v)
double Voltage::toVolts(int sensorValue) {
  return sensorValue / VOLTS_SCALE;
}

bool Voltage::read() {
  // read the analog in value:
  m_sensorValue = analogRead(m_pin);

  // map it to a voltage
  m_voltage = toVolts(m_sensorValue);

  return true;
}
