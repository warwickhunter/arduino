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
#include <WString.h>

// Set this to 1 if you want the Arduino to go into low power mode between each sample
#define WITH_SLEEP 0

const int           SHORT_PAUSE    = 20;
const unsigned long SERIAL_SPEED   = 9600;
const long          SLEEP_INTERVAL = 5000;

const int LED_PIN      = 13; // Pin 13 has an LED connected on most Arduino boards:
const int DHT11_PIN    = 7;  // Digital PIN 7 to which the DHT11 temp sensor is attached
const int VOLTAGE_PIN  = 0;  // Analog input pin to which the voltage divider is attached

long        sequenceNumber = 0;
Voltage     voltage(VOLTAGE_PIN);
Temperature temperature(DHT11_PIN);

void setup() {
    Serial.begin(SERIAL_SPEED);
    pinMode(LED_PIN, OUTPUT);
    voltage.setup();
    temperature.setup();
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

    digitalWrite(LED_PIN, LOW);  // set the LED off

    delay(SLEEP_INTERVAL);
}
