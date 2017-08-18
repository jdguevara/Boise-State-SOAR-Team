#include <Adafruit_MAX31865.h>

// CS pin
#define MAX31865_CS 7
// The value of the Rref resistor. Use 430.0!
#define RREF 430.0

// Use hardware SPI, just pass in the CS pin
Adafruit_MAX31865 max = Adafruit_MAX31865(MAX31865_CS);

void setup() {
  Serial.begin(115200);
  max.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
}

void loop() {
  Serial.print("Temperature = "); 
  Serial.println(max.temperature(100, RREF));
  Serial.println();
  delay(1000);
}
