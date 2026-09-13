int ledPin = 3; // Built-in LED pin

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin as an output
}

void loop() {
  digitalWrite(ledPin, HIGH); // Turn LED on
  delay(1000);                // Wait for 1 second
  digitalWrite(ledPin, LOW);  // Turn LED off
  delay(1000);                // Wait for 1 second
}

