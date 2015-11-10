#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

const int BUTTON_PIN     = 2 ;   // The number of the pushbutton pin
const int NEOPIXEL_PIN   = 6 ;   // The number of the LED pin
const int NUMPIXELS      = 30 ;  // The number of LEDs in the LED strip.

int  pixelOffset         = 0 ; 
int  lastButtonState     = HIGH;  // the previous reading from the input pin

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // This initializes the NeoPixel library.
  pinMode(BUTTON_PIN, INPUT_PULLUP); // initialize the pushbutton pin as an input and high by default.
}

void loop() {
  // read the state of the switch into a local variable:
  int buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState != lastButtonState ) { // Check to see if the button has changed state
    lastButtonState = buttonState ; // The button has changed state, update the last button state. 
    if( buttonState == LOW ) { // check to see if the button is currently down., 
      
      strip.setPixelColor(pixelOffset, strip.Color(0,0,0)); // Set the perviouse led to black. 

      pixelOffset ++ ; 
      if( pixelOffset >= NUMPIXELS ) {
        pixelOffset = 0 ; 
      }

      strip.setPixelColor(pixelOffset, strip.Color(150,0,0)); // RED 
      strip.show(); // This sends the updated pixel color to the hardware. 
    }
  }
}



