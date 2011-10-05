/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 *  Manage placing the system into low power mode and bringing
 *  it out of lower power mode by the use of the watchdog timer
 *  interrupt.
 *
 *  Created on: 2011-10-05
 *      Author: Warwick Hunter
 */

#ifndef POWERSAVE_H_
#define POWERSAVE_H_

class PowerSave {
public:
    explicit PowerSave();

    /** Perform any once only setup */
    void setup();

    /** Put the system to sleep for a number of seconds */
    void sleep();

private:
    void watchdogSetup(int delay);
};

inline PowerSave::PowerSave() {
}

#endif /* POWERSAVE_H_ */
