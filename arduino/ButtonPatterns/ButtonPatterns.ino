#define LED_PIN       13   // the number of the LED pin
#define BUTTON_PIN     2   // the number of the pushbutton pin
int buttonState;            // variable for reading the pushbutton status
int pattern ;               // variable what pattern we are on.
 
void setup() { 
  pinMode(LED_PIN, OUTPUT);   // initialize the LED pin as an output 
  pinMode(BUTTON_PIN, INPUT); // initialize the pushbutton pin as an input
  pattern = 0;                // Set the initial pattern 
}
void loop() {
  buttonState = digitalRead(BUTTON_PIN); // read the state of the pushbutton value
  if (buttonState == HIGH) {             // If the button has been pressed, 
    pattern++;                           // Change the pattern.
  }

  if( pattern == 1) {
    BlinkLEDFast(); 
  } else if( pattern == 2) {
    BlinkLEDSlow(); 
  } else {                               // If pattern is zero or higher than 3, set 
    pattern = 0 ;                        // the pattern back to zero. This ensures that 
    BlinkLEDPattern();                   // the pattern variable is always 0,1,2 
  }
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

