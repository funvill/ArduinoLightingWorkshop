#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define LEDS_PIN        6
#define NUMPIXELS      30   // the number of LEDs 
#define BUTTON_PIN      2   // the number of the pushbutton pin
int cursor ;                // location of the cursor 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LEDS_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // This initializes the NeoPixel library.  
  pinMode(BUTTON_PIN, INPUT_PULLUP); // initialize the pushbutton pin as an input
  cursor = 0 ; 
  strip.setBrightness(128); // Half brightness
}

void loop() {

  static long lastDebounceTime = 0;  // the last time the output pin was toggled
  static int lastButtonState = HIGH ; 

  int reading = digitalRead(BUTTON_PIN);  // read the state of the pushbutton value
  if( reading != lastButtonState ) { 
    lastButtonState = reading ; 
    if (reading == LOW && millis() - lastDebounceTime > 200 ) {             // If the button has been pressed,       
      lastDebounceTime = millis(); 
      cursor++;                           // Change the pattern.
    }
  }
  if( cursor > strip.numPixels() ) {
    // Reset the LEDs 
    for( cursor = 0; cursor <= strip.numPixels(); cursor++ ) {
      strip.setPixelColor(cursor, strip.Color(0,0,0)); 
    }
    cursor = 0 ; 
  }

 strip.setPixelColor(cursor, strip.Color(255,0,0)); 
 strip.show(); 

}


