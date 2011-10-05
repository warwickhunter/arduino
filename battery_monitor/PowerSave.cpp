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

#include "PowerSave.h"
#include <Arduino.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

/** Perform any once only setup */
void PowerSave::setup() {
    // Set the watchdog to interrupt every 8 seconds, which is the longest period
    watchdogSetup(WDTO_8S);
}

/** Put the system to sleep for a number of seconds */
void PowerSave::sleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Use the mode that saves the most power
    sleep_enable();
    sleep_mode();                        // System sleeps here
    sleep_disable();                     // System continues execution here when watchdog times out
}

/**
 * Set the watchdog to interrupt every few seconds and not reset the system
 * 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms, 6=1 sec,7=2 sec, 8=4 sec, 9=8sec
 * See the constants defined in avr/wdt.h.
 */
void PowerSave::watchdogSetup(int delay) {

  byte bb;
  if (delay > 9 ) delay=9;
  bb=delay & 7;
  if (delay > 7) bb|= (1<<5);
  bb|= (1<<WDCE);

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCSR = bb;
  WDTCSR |= _BV(WDIE);
}

//****************************************************************
// Watchdog Interrupt Service / is executed when  watchdog timed out
ISR(WDT_vect) {
}
