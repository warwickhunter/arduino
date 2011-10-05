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
#if ARDUINO == 22
#include <WProgram.h>
#endif
#if ARDUINO == 100
#include <Arduino.h>
#endif

#include "Voltage.h"
#include "Temperature.h"
#include "PowerSave.h"


static const int LED_PIN     = 13; // Pin 13 has an LED connected on most Arduino boards:
static const int DHT11_PIN   = 4;  // Digital PIN 4 to which the DHT11 temp sensor is attached
static const int VOLTAGE_PIN = 0;  // Analog input pin to which the voltage divider is attached

static Voltage     voltage(VOLTAGE_PIN);
static Temperature temperature(DHT11_PIN);
static PowerSave   powerSave;

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    voltage.setup();
    temperature.setup();
    powerSave.setup();
    Serial.println("Battery Monitor v1.0, build " __DATE__ " " __TIME__);
}

void loop() {
    digitalWrite(LED_PIN, HIGH);  // set the LED on

    if (temperature.read()) {
        Serial.print("Humidity = ");
        Serial.print(temperature.getHumidity(), 1);
        Serial.print(" Temperature = ");
        Serial.print(temperature.getTemperature(), 1);
    }
    if (voltage.read()) {
        Serial.print(" Voltage = ");
        Serial.print(voltage.getVoltage());
    }
    Serial.println();
    Serial.flush();
    // Give the serial output a chance to complete before sleeping
    delay(20);

    digitalWrite(LED_PIN, LOW);  // set the LED off

    powerSave.sleep();
}

#if ARDUINO == 22
int main(void) {
    init();
    setup();
    for (;;) {
        loop();
    }
    return 0;
}
#endif
