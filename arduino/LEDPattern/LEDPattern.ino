#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define PIN            6
#define NUMPIXELS      30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // This initializes the NeoPixel library.
}
void loop() {
  // Instead of incrementing the for loop by 1, increment by 3
  for( int pixel = 0; pixel < strip.numPixels(); pixel +=3 ) { 
     strip.setPixelColor(pixel  , strip.Color(150,0,0)); // bright red color.
     strip.setPixelColor(pixel+1, strip.Color(0,150,0)); // bright green color.
     strip.setPixelColor(pixel+2, strip.Color(0,0,150)); // bright blue color.
  }
  strip.show(); // This sends the updated pixel color to the hardware.
}
