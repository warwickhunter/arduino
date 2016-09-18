
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

DHT dht(DHT11_PIN, DHT11);

/** Arduino setup, called once only */
void setup() {
    uView.begin();
    dht.begin();
}

/** Show the date and time of this build */
void splashScreen() {
    uView.setFontType(0); // Use the default 5x7 pixel font
    uView.clear(PAGE);
    uView.setCursor(0, 0);
    uView.println("Wasa's\nWeather\n");
    uView.println("2016-09-18");
    uView.println(__TIME__);
    uView.display();
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

/** Show the temperature and humidity on two lines in the large font */
void drawValues(float temperature, float humidity) {
    uView.setFontType(1); // Use the large 8x16 pixel font

    uView.setCursor(X, Y1);
    uView.print(temperature, 1);
    uView.println(" C");

    uView.setCursor(X, Y2);
    uView.print(humidity, 1);
    uView.println(" %");
}

int sampleCount = 0;
bool isFirstTime = true;

/** Arduino loop method, called continually forever */
void loop() {

    if (isFirstTime) {
        splashScreen();
        delay(SPLASH);
        isFirstTime = false;
    }

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    uView.clear(PAGE);
    drawValues(temperature, humidity);
    drawUpdateIndicator(sampleCount);
    uView.display();

    delay(DELAY);

    ++sampleCount;
    if (sampleCount > 30) {
        sampleCount = 0;
    }
}
