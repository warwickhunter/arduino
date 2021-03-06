/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * voltage divider attached from analogue pin 0 to ground
 * LED connected from digital pin 9 to ground
 
 created 29 Dec. 2008
 Modified 4 Sep 2010
 by Tom Igoe
 Modified 28 Sep 2011
 by Warwick Hunter
 
 This example code is in the public domain.
 
 Calibration of the voltage divider. The divisor appears to be 5.1005.

                   0.00v == sensor 0    ouptut == 0
 9.13v / 5.1005 == 1.79v == sensor 384  output == 95
                   3.28v == sensor 705  output == 175
                   4.78v == sensor 1023 output == 255 
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = 0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 13; // Analog output pin that the LED is attached to

// The scaling factor that converts the sensor reading to a voltage. This has been calibrated 
// with a volt meter and compensates for some inaccuracy in the voltage divider.
const double VOLTS_SCALE = 1051.47 / 25.0;

int    sensorValue = 0;        // value read from the analogue input pin
int    outputValue = 0;        // value output to the PWM (analog out)
double voltage     = 0.0;      // voltage calculated

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

// Scale the value of the sensor (0-1023) to be volts (0-25v)
double toVolts(int sensorValue) {
  return sensorValue / VOLTS_SCALE;
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            

  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  

  // map it to a voltage
  voltage = toVolts(sensorValue);

  // change the analog out value:
  analogWrite(analogOutPin, outputValue);           

  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.print(outputValue);   
  Serial.print("\t voltage = ");      
  Serial.println(voltage);   

  // wait at least 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(150);                     
}
