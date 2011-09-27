/*
  Blink
  Turns on an LED on for a period, then off for a period, repeatedly.
 
  This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards:
const int LED_PIN = 13;

void setup() {                
    // initialize the digital pin as an output.
    pinMode(LED_PIN, OUTPUT);     
}

void loop() {
    for (int i = 1; i < 10; ++i) {
        digitalWrite(LED_PIN, HIGH);  // set the LED on
        delay(25 * i);                // wait for a variable time
        digitalWrite(LED_PIN, LOW);   // set the LED off
        delay(25 * i);                // wait for a variable time
    }
}
