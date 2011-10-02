/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  The methods used to control and monitor the voltage divider.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */

#ifndef VOLTAGE_DIVIDER_H_
#define VOLTAGE_DIVIDER_H_

class VoltageDivider {

public:
    explicit VoltageDivider(int analoguePinNumber);
    virtual ~VoltageDivider();

    virtual void setup();

private:
    int m_pin;
};

#endif /* VOLTAGE_DIVIDER_H_ */
