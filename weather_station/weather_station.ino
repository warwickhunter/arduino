/**
 * A small weather station that uses the display of the Microview and the DHT11 temperature/humidity sensor.
 * 
 * Warwick Hunter 2016-09-14
 */
#include <MicroView.h>
#include <DHT_U.h>

const int DHT11_PIN = 0; // Digital PIN 0

DHT dht(DHT11_PIN, DHT11);

void printHeader()
{
    Serial.println();
    Serial.println("Humidity (%)\tTemperature (C)");
}

void setup() {
    uView.begin();
    dht.begin();
    Serial.begin(9600);
    Serial.println("DHT TEST PROGRAM ");
    Serial.println(__DATE__ " " __TIME__);
    printHeader();
}

int sampleCount = 0;

void loop() {

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.println(temperature, 1);

    ++sampleCount;
    if (sampleCount > 20) {
        printHeader();
        sampleCount = 0;
    }

    uView.clear(PAGE);
    uView.setCursor(0, 0);
    uView.print(temperature, 1);
    uView.println(" C");
    uView.print(humidity, 1);
    uView.println(" %");
  
    uView.display();
    delay(2000);
}
