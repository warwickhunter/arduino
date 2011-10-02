/*
 * Copyright Warwick Hunter 2011. All rights reserved.
 *
 * This is the main loop for the battery charger monitor Arduino application.
 *
 *  Created on: 2011-10-01
 *      Author: Warwick Hunter
 */
#include <WProgram.h>
#include "VoltageDivider.h"
#include "TemperatureSensor.h"

static const int DHT11_PIN   = 4; // Digital PIN 4 to which the DHT11 temp sensor is attached
static const int VOLTAGE_PIN = 0; // Analog input pin to which the voltage divider is attached

static VoltageDivider    voltageDivider(VOLTAGE_PIN);
static TemperatureSensor temperatureSensor(DHT11_PIN);

void setup() {
    Serial.begin(115200);
    voltageDivider.setup();
    temperatureSensor.setup();
}

void loop() {
    if (temperatureSensor.read()) {
        Serial.print("Humidity = ");
        Serial.print(temperatureSensor.getHumidity(), 1);
        Serial.print(" Temperature = ");
        Serial.println(temperatureSensor.getTemperature(), 1);
    }
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
