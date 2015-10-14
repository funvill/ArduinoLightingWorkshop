#define POT_PIN  0      // Select the input pin for the potentiometer
#define LED_PIN  13     // Select the pin for the LED
void setup() {
   pinMode(LED_PIN, OUTPUT);                      // Declare the ledPin as an OUTPUT
}
void loop() {
  int sensorValue = analogRead(POT_PIN);          // Read the value from the sensor
  int val = map(sensorValue, 0, 1024, 100, 1000); // Change sensorValue to a number between
                                                  //  100-1000 (0.1 and 1 seconds) 
  digitalWrite(LED_PIN, HIGH);                    // Turn the ledPin on
  delay(val);                                     // Stop the program for some time
  digitalWrite(LED_PIN, LOW);                     // Turn the ledPin off
  delay(val);                                     // Stop the program for some time
}

