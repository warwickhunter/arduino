/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 * This is an experiment with the Arduino sleep mode and the watchdog timer.
 * When the board is sleeping it consumes 19mA, when it is awake it consumes
 * 80mA.
 *
 *  Created on: 2011-10-05
 *      Author: Warwick Hunter
 */
#include <Arduino.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

// Pin 13 has an LED connected on most Arduino boards:
const int LED_PIN = 13;

int counter = 0;
volatile int wdtFired = 0;


/**
 * Set the watchdog to interrupt every few seconds and not reset the system
 * 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms, 6=1 sec,7=2 sec, 8=4 sec, 9=8sec
 */
void watchdogSetup(int delay) {

  byte bb;
  int ww;
  if (delay > 9 ) delay=9;
  bb=delay & 7;
  if (delay > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCSR = bb;
  WDTCSR |= _BV(WDIE);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Sleepy, build " __DATE__ " " __TIME__);

    pinMode(LED_PIN, OUTPUT);

    watchdogSetup(WDTO_8S);
}

void loop() {
    Serial.print("sleepy ");
    Serial.print(++counter);
    Serial.print(" wdtFired=");
    Serial.println(wdtFired);
    Serial.flush();
    wdtFired = 0;
    digitalWrite(LED_PIN, HIGH);  // set the LED on
    delay(250);
    digitalWrite(LED_PIN, LOW);  // set the LED on

    Serial.print("sleeping... ");
    Serial.flush();
    delay(20);

    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
    sleep_enable();
    sleep_mode();                        // System sleeps here
    sleep_disable();                     // System continues execution here when watchdog timed out

    Serial.println("awake");
    Serial.flush();
    delay(8000);
}

//****************************************************************
// Watchdog Interrupt Service / is executed when  watchdog timed out
ISR(WDT_vect) {
  wdtFired = 1;  // set global flag to indicate WDT has fired
}
