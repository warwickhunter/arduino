/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 * This is the main loop for the battery charger monitor Arduino application.
 * It monitors a voltage divider attached to the battery terminals and a DHT11
 * digital temperature and humidity sensor.
 *
 * The system uses 80mA when awake and 19mA when asleep. This was measured before
 * any wireless communications were added to the board.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */
#include <Arduino.h>
#include "Voltage.h"
#include "Temperature.h"
#include "PowerSave.h"
#include <WString.h>

const int           PAUSE        = 20;
const unsigned long SERIAL_SPEED = 9600;

const int LED_PIN      = 13; // Pin 13 has an LED connected on most Arduino boards:
const int DHT11_PIN    = 4;  // Digital PIN 4 to which the DHT11 temp sensor is attached
const int VOLTAGE_PIN  = 0;  // Analog input pin to which the voltage divider is attached

Voltage     voltage(VOLTAGE_PIN);
Temperature temperature(DHT11_PIN);
PowerSave   powerSave;
long        sequenceNumber = 0;

void setup() {
    Serial.begin(SERIAL_SPEED);
    pinMode(LED_PIN, OUTPUT);
    voltage.setup();
    temperature.setup();
    powerSave.setup();
    Serial.println(F("\n\nBattery Monitor v1.0, build " __DATE__ " " __TIME__));
}

void loop() {
    digitalWrite(LED_PIN, HIGH);  // set the LED on

    Serial.print(F("Seq="));
    Serial.print(sequenceNumber++);

    if (temperature.read()) {
        Serial.print(F(" Humidity="));
        Serial.print(temperature.getHumidity(), 1);
        Serial.print(F(" Temperature="));
        Serial.print(temperature.getTemperature(), 1);
    }
    if (voltage.read()) {
        Serial.print(F(" Voltage="));
        Serial.print(voltage.getVoltage());
    }
    Serial.println();
    Serial.flush();
    // Give the serial output a chance to complete before sleeping
    delay(PAUSE);

    digitalWrite(LED_PIN, LOW);  // set the LED off

    powerSave.sleep();
}
