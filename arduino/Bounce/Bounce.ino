#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define LEDS_PIN        6
#define NUMPIXELS      30   // the number of LEDs 
#define BUTTON_PIN      2   // the number of the pushbutton pin
int pattern ;               // variable what pattern we are on.
int cursor ;                // location of the cursor 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LEDS_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // This initializes the NeoPixel library.  
  pinMode(BUTTON_PIN, INPUT_PULLUP); // initialize the pushbutton pin as an input
  pattern = 0;                // Set the initial pattern 
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
      pattern++;                           // Change the pattern.
    }
  }


  if( pattern == 1) {
    ManualControl();
  } else {                               
    pattern = 0 ;
    BounceWithColor();                     
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
void ManualControl() {
  int sensorValueZero = analogRead(0);       // Read the value from sensor zero
  int sensorValueOne  = analogRead(1);       // Read the value from sensor one
  int sensorValueTwo  = analogRead(2);       // Read the value from sensor two 
  int valRed   = map(sensorValueZero, 0, 1024, 0, 254); // Map the value to 0-255
  int valGreen = map(sensorValueOne,  0, 1024, 0, 254); // Map the value to 0-255 
  int valBlue  = map(sensorValueTwo,  0, 1024, 0, 254); // Map the value to 0-255 

  for( int pixel = 0; pixel < strip.numPixels(); pixel++ ) {
     strip.setPixelColor(pixel, strip.Color(valRed,valGreen,valBlue)); 
  }
  strip.show(); // This sends the updated pixel color to the hardware.
}


void BounceWithColor() {
  int valColorOne = map(analogRead(0), 0, 1024,  0, 254); // Map the value to 0-254
  int valColorTwo = map(analogRead(1), 0, 1024,  0, 254);   // Map the value to 2-10 
  int valSpeed    = map(analogRead(2), 0, 1024, 10, 100); // Map the value to 20-254 

  static int dir = 1 ; 
  static bool colorState = false; 
  if (colorState) {
    strip.setPixelColor(cursor, Wheel(valColorOne));
  }
  else {
    strip.setPixelColor(cursor, Wheel(valColorTwo));
  }

  strip.show(); // This sends the updated pixel color to the hardware.
  cursor += dir ;
  if (cursor > strip.numPixels() | cursor < 0 ) {
    dir *= -1 ;
    colorState = !colorState; 
  }
  delay(valSpeed);

}


