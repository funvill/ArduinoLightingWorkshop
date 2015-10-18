#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define LEDS_PIN        6
#define NUMPIXELS      30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LEDS_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  strip.begin(); // This initializes the NeoPixel library.
}

void loop() {
  strip.setPixelColor(1, strip.Color(0,150,0)); // Moderately bright green color.
  strip.show(); // This sends the updated pixel color to the hardware.
}
