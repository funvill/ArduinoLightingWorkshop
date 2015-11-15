#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

const int KNOB_ONE_PIN   = A0 ; 
const int KNOB_TWO_PIN   = A1 ; 
const int KNOB_THREE_PIN = A2 ; 
const int BUTTON_PIN     =  2 ;  // The number of the pushbutton pin
const int NEOPIXEL_PIN   =  6 ;  // The number of the LED pin
const int NUMPIXELS      = 30 ;  // The number of LEDs in the LED strip.

int mode ; 

const int MODE_RAINBOW      = 0; 
const int MODE_RGB_CONTROL  = 1; 
const int MODE_CURSOR       = 2; 
const int MODE_COLOR_WIPE   = 3; 




Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // This initializes the NeoPixel library.
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Initialize the pushbutton pin as an input 
                                     // and high by default.
  Serial.begin(9600); // initialize serial communications at 9600 bps:
}

void loop() {  
  // Check button state. 
  static int lastButtonState = HIGH; 
  int buttonState = digitalRead(BUTTON_PIN); // read the state of the button. 
  if (buttonState != lastButtonState ) { // Check to see if the button has changed state
    lastButtonState = buttonState ; // The button changed, update the last button state.
    if( buttonState == LOW ) { // check to see if the button is currently down.
      Serial.print("Button has pressed...");
      mode++ ; 
    }
  }

  // Depending on the mode show a different pattern.   
  Serial.println("mode=" + String(mode) );
  switch( mode ) {
    case MODE_RGB_CONTROL:
    {
      ModeRGBControl(); 
      break ;
    } 
    case MODE_CURSOR: {
      Cursors(); 
      break ;
    } 
    case MODE_COLOR_WIPE: {
      ColorWipe(); 
      break ;
    }    
    case MODE_RAINBOW: 
    default: 
    {
      mode = 0 ; 
      ModeRainbow(); 
      break ; 
    }
  }
}

void ModeRGBControl() {
  
  int potOneValue   = analogRead(KNOB_ONE_PIN);
  int potTwoValue   = analogRead(KNOB_TWO_PIN);
  int potThreeValue = analogRead(KNOB_THREE_PIN);
  
  unsigned char red   = map(potOneValue,0,1023,0,255) ; 
  unsigned char green = map(potTwoValue,0,1023,0,255) ;
  unsigned char blue  = map(potThreeValue,0,1023,0,255) ;   

  // print the results
  Serial.print("RED=" + String(potOneValue) + " (" + String(red) + ") ");
  Serial.print("GREEN=" + String(potTwoValue) + " (" + String(green) + ") ");
  Serial.println("BLUE=" + String(potThreeValue) + " (" + String(blue) + ") ");

  for( int pixel = 0 ; pixel < NUMPIXELS ; pixel++ ) {    
    strip.setPixelColor(pixel, strip.Color(red,green,blue)); 
  }
  strip.show(); // This sends the updated pixel color to the hardware.
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void ModeRainbow() {

  uint16_t cursorPos = map(analogRead(KNOB_TWO_PIN),0,1023,0,255) ;

  static uint16_t j = 0 ;   
  if( cursorPos == 0 ) {
    // Roating rainbow. 
     
    for(uint16_t i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    j++; 
  } else {
    j = cursorPos ; 
    for(uint16_t i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j ) & 255));
    }
    
  }
  strip.show();
  delay(10);
  
}

void Cursors() {
 
  uint32_t backgroundColor = Wheel( map(analogRead(KNOB_ONE_PIN),0,1023,0,255)) ; 
  uint32_t cursorColor     = Wheel( map(analogRead(KNOB_TWO_PIN),0,1023,0,255)) ; 
  uint16_t cursorPos       = map(analogRead(KNOB_THREE_PIN),0,1023,0,strip.numPixels()) ;

 
  for(uint16_t i=0; i< strip.numPixels(); i++) {
    if( i == cursorPos ) {
      // Set the color of the cursor 
      strip.setPixelColor(i, cursorColor );
    } else {
       // Set the background color.
       strip.setPixelColor(i, backgroundColor );
    }    
  }  
  strip.show();
}

void ColorWipe() {
  uint32_t oneColor      = Wheel( map(analogRead(KNOB_ONE_PIN),  0,1023,0,255)) ; 
  uint32_t twoColor      = Wheel( map(analogRead(KNOB_TWO_PIN),  0,1023,0,255)) ;
  uint32_t rotationSpeed = map(analogRead(KNOB_THREE_PIN),0,1023,5,40) ; 

  static unsigned char wipeMode = 0 ;
  static uint32_t pixelCursor = 0 ;
   
  pixelCursor++ ; 
  if( pixelCursor > strip.numPixels() ) {
    wipeMode++; 
    pixelCursor = 0 ; 
  }

  if( wipeMode >= 2 ) {
    wipeMode = 0 ; 
    pixelCursor = 0 ; 
  }
  
  switch( wipeMode ) {
    default: 
    case 0: {
      strip.setPixelColor(pixelCursor, oneColor );
      break; 
    }
    case 1: {
      strip.setPixelColor(pixelCursor, twoColor );
      break; 
    }    
  }  
  
  delay(rotationSpeed);
  strip.show();
}



