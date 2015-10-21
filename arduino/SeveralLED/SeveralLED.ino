#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define PIN            6
#define NUMPIXELS      30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // This initializes the NeoPixel library.
}
void loop() {
  strip.setPixelColor(0, strip.Color(150,0,0)); // Moderately bright red color.
  strip.setPixelColor(1, strip.Color(0,150,0)); // Moderately bright green color.
  strip.setPixelColor(2, strip.Color(0,0,150)); // Moderately bright blue color.
  strip.show(); // This sends the updated pixel color to the hardware.
}
