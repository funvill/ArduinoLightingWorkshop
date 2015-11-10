const int KNOB_ONE_PIN   = A0 ; 
const int KNOB_TWO_PIN   = A1 ; 
const int KNOB_THREE_PIN = A2 ; 

void setup() {
  Serial.begin(9600); // initialize serial communications at 9600 bps:
}

void loop() {  

  int potOneValue   = analogRead(KNOB_ONE_PIN);
  int potTwoValue   = analogRead(KNOB_TWO_PIN);
  int potThreeValue = analogRead(KNOB_THREE_PIN);

  // print the results to the serial monitor:
  Serial.print("One = " );
  Serial.print(potOneValue);
  Serial.print(" (");
  Serial.print(map(potOneValue,0,1023,0,255));

  Serial.print(")   Two = " );
  Serial.print(potTwoValue);
  Serial.print(" (");
  Serial.print(map(potTwoValue,0,1023,0,255));

  Serial.print(")   Three = " );
  Serial.print(potThreeValue);
  Serial.print(" (");
  Serial.print(map(potThreeValue,0,1023,0,255));
  Serial.println(")"); 

}



