const int buzzerPin = 5; // Buzzer connected to digital pin 8

void setup() {
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as an OUTPUT
}

void loop() {
  digitalWrite(buzzerPin, HIGH); // Turn the buzzer ON
  delay(1000);                   // Wait for 1 second (1000 milliseconds)
  
  digitalWrite(buzzerPin, LOW);  // Turn the buzzer OFF
  delay(1000);                   // Wait for 1 second
}
