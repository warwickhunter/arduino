
/**
 * A small weather station that uses the display of the Microview and the DHT11 temperature/humidity sensor.
 * 
 * @author Warwick Hunter 
 * @since  2016-09-14
 */
#include <MicroView.h>
#include <DHT_U.h>

const int DHT11_PIN = 6;    // Digital PIN 6 is comms to the DHT11
const int X         = 4;    // X of all lines of text
const int Y1        = 8;    // Y of first line of text
const int Y2        = 24;   // Y of second line of text
const int DELAY     = 2000; // 2 seconds in between each screen update
const int SPLASH    = 4000; // Display splash screen for 4 seconds

#define USE_SERIAL 0 // Output to serial as well

DHT dht(DHT11_PIN, DHT11);

void printHeader() {
#if USE_SERIAL    
    Serial.println();
    Serial.println("Humidity (%)\tTemperature (C)");
#endif // USE_SERIAL
}

void printValues(float humidity, float temperature) {
#if USE_SERIAL    
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.println(temperature, 1);
#endif // USE_SERIAL
}

void setupSerial() {
#if USE_SERIAL    
    Serial.begin(9600);
    Serial.println("Wasa's Weather");
    Serial.println("2016-09-18");
    Serial.println(__TIME__);
    printHeader();
#endif // USE_SERIAL
}

/** Show the date and time of this build */
void splashScreen() {
    uView.clear(PAGE);
    uView.setCursor(0, 0);
    uView.println("Wasa's\nWeather\n");
    uView.println("2016-09-18");
    uView.println(__TIME__);
    uView.display();
}

void setup() {
    uView.begin();
    dht.begin();
    setupSerial();
}

/** 
 * Draw pixels to show that that the display is being updated even 
 * if the temp and humidity stay the same.
 */
void drawUpdateIndicator(int sampleCount) {
    int x = sampleCount * 2;
    int y = LCDHEIGHT - 1;  
    uView.pixel(x,     y);
    uView.pixel(x + 1, y);
    uView.pixel(x + 2, y);
    uView.pixel(x,     y - 1);
    uView.pixel(x + 1, y - 1);
    uView.pixel(x + 2, y - 1);
    uView.pixel(x,     y - 2);
    uView.pixel(x + 1, y - 2);
    uView.pixel(x + 2, y - 2);
}

int sampleCount = 0;
bool isFirstTime = true;

void loop() {

    if (isFirstTime) {
        splashScreen();
        delay(SPLASH);
        isFirstTime = false;
    }
    uView.setFontType(1);

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    printValues(humidity, temperature);

    ++sampleCount;
    if (sampleCount > 30) {
        printHeader();
        sampleCount = 0;
    }

    uView.clear(PAGE);
    uView.setCursor(X, Y1);
    uView.print(temperature, 1);
    uView.println(" C");

    uView.setCursor(X, Y2);
    uView.print(humidity, 1);
    uView.println(" %");

    drawUpdateIndicator(sampleCount);
  
    uView.display();
    delay(DELAY);
}
