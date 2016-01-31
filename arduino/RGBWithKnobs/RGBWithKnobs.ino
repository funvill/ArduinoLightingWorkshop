#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

const int KNOB_ONE_PIN   = A0 ; 
const int KNOB_TWO_PIN   = A1 ; 
const int KNOB_THREE_PIN = A2 ; 
const int BUTTON_PIN     =  2 ;  // The number of the pushbutton pin
const int NEOPIXEL_PIN   =  6 ;  // The number of the LED pin
const int NUMPIXELS      = 30 ;  // The number of LEDs in the LED strip.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // This initializes the NeoPixel library.
  pinMode(BUTTON_PIN, INPUT_PULLUP); // initialize the pushbutton pin as an input and high by default.
  
  Serial.begin(9600); // initialize serial communications at 9600 bps:
}

void loop() {  

  int potOneValue   = analogRead(KNOB_ONE_PIN);
  int potTwoValue   = analogRead(KNOB_TWO_PIN);
  int potThreeValue = analogRead(KNOB_THREE_PIN);

  unsigned char red   = map(potOneValue,0,1023,0,255) ; 
  unsigned char green = map(potTwoValue,0,1023,0,255) ; 
  unsigned char blue  = map(potThreeValue,0,1023,0,255) ; 

  // print the results to the serial monitor:
  Serial.print("One="     + String(potOneValue)   + " (" + String(red)   + ") ");
  Serial.print("Two="     + String(potTwoValue)   + " (" + String(green) + ") ");
  Serial.println("Three=" + String(potThreeValue) + " (" + String(blue)  + ") "); 

  for( int pixel = 0 ; pixel < NUMPIXELS ; pixel++ ) {    
    strip.setPixelColor(pixel, strip.Color(red,green,blue)); 
  }
  strip.show(); // This sends the updated pixel color to the hardware.
}



