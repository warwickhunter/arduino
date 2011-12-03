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
 *  8.84v / x == 1.73v == sensor 375
 *  7.81v / x == 1.53v == sensor 354
 *
 *  Here is how I work out the scale factor. 7.81v is measured at the battery.
 *
 *  sensor / scale == volts
 *  354 / scale == 7.81v
 *  354 == 7.81 * scale
 *  354/7.81 == scale
 *  354/7.81 == 45.326
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */

#include "Voltage.h"
#include <Arduino.h>

// The scaling factor that converts the sensor reading to a voltage. This has been calibrated
// with a volt meter and compensates for some inaccuracy in the voltage divider.
const double VOLTS_SCALE = 45.326;

// Scale the value of the sensor (0-1023) to be volts (0-25v)
double Voltage::toVolts(int sensorValue) {
  return sensorValue / VOLTS_SCALE;
}

bool Voltage::read() {
  // read the analogue input value
  m_sensorValue = analogRead(m_pin);

  // scale the input value to a voltage
  m_voltage = toVolts(m_sensorValue);

  return true;
}
