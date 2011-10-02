/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  The methods used to control and monitor the voltage divider.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */

#include "VoltageDivider.h"

VoltageDivider::VoltageDivider(int analoguePinNumber)
    : m_pin(analoguePinNumber) {
}

VoltageDivider::~VoltageDivider() {
}

void VoltageDivider::setup() {
}
