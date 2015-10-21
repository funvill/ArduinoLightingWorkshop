#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define LED_PIN        13
#define LEDS_PIN        6
#define NUMPIXELS      30   // the number of LEDs 
#define BUTTON_PIN      2   // the number of the pushbutton pin

int buttonState;            // variable for reading the pushbutton status
int pattern ;               // variable what pattern we are on.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LEDS_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // This initializes the NeoPixel library.  
  pinMode(LED_PIN, OUTPUT);   // initialize the LED pin as an output 
  pinMode(BUTTON_PIN, INPUT); // initialize the pushbutton pin as an input
  pattern = 0;                // Set the initial pattern 
  strip.setBrightness(128);   // Half brightness
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);  // read the state of the pushbutton value
  if (buttonState == HIGH) {             // If the button has been pressed, 
    pattern++;                           // Change the pattern.
  }

  if( pattern == 1) {
    BlinkLEDFast(); 
  } else if( pattern == 2) {
    BlinkLEDSlow(); 
  } else if (pattern == 3) { 
    BlinkLEDPattern(); 
  } else {                               // If pattern is zero or higher than 4, set 
    pattern = 0 ;                        // the pattern back to zero. This ensures that 
    ManualControl();                     // the pattern variable is always 0,1,2,3 
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
// Blink the LED really fast (100ms) 
void BlinkLEDFast() {
  digitalWrite(LED_PIN, HIGH);
  delay(100);                
  digitalWrite(LED_PIN, LOW);
  delay(100);           
}

// Blink the LED slow (1 second ) 
void BlinkLEDSlow() {
  digitalWrite(LED_PIN, HIGH);
  delay(1000);                
  digitalWrite(LED_PIN, LOW);
  delay(1000);           
}
// Blink the LED with a pattern
void BlinkLEDPattern() {
  digitalWrite(LED_PIN, HIGH);
  delay(1000);                
  digitalWrite(LED_PIN, LOW);
  delay(100);           
}

