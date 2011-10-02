/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 * This is the main loop for the battery charger monitor Arduino application.
 * It monitors a voltage divider attached to the battery terminals and a DHT11
 * digital temperature and humidity sensor.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */
#include <WProgram.h>
#include "Voltage.h"
#include "Temperature.h"

static const int DHT11_PIN   = 4; // Digital PIN 4 to which the DHT11 temp sensor is attached
static const int VOLTAGE_PIN = 0; // Analog input pin to which the voltage divider is attached

static Voltage    voltage(VOLTAGE_PIN);
static Temperature temperature(DHT11_PIN);

void setup() {
    Serial.begin(115200);
    voltage.setup();
    temperature.setup();
}

void loop() {
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
    delay(1000);
}

int main(void) {
    init();
    setup();
    for (;;) {
        loop();
    }
    return 0;
}
