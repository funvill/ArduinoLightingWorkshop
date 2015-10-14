#define LED_PIN  13                          // Select the pin for the LED
void setup() {
   pinMode(LED_PIN, OUTPUT);                  // Declare the ledPin as an OUTPUT
}
void loop() {
  int sensorValueZero = analogRead(0);       // Read the value from sensor zero
  int sensorValueOne  = analogRead(1);       // Read the value from sensor one
  int sensorValueTwo  = analogRead(2);       // Read the value from sensor two 
  int valZero = map(sensorValueZero, 0, 1024, 0, 1000); // Map the value to one second 
  int valOne  = map(sensorValueOne,  0, 1024, 0, 1000); // Map the value to one second 
  int valTwo  = map(sensorValueTwo,  0, 1024, 0, 1000); // Map the value to one second 

  // Add up all the values from the sensors, use this as a delay for your blinking LED. 
  digitalWrite(LED_PIN, HIGH);                 // Turn the ledPin on
  delay(valZero + valOne + valTwo );          // Stop the program for some time
  digitalWrite(LED_PIN, LOW);                  // Turn the ledPin off
  delay(valZero + valOne + valTwo );          // Stop the program for some time
}

