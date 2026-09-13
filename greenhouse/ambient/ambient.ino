const int lightPin = A0; // Define the analog pin for the light sensor

void setup() {
  Serial.begin(9600);    // Start serial communication at 9600 baud
}

void loop() {
  int lightValue = analogRead(lightPin); // Read the analog value (0 to 1023)
  
  Serial.print("Light Intensity: ");
  Serial.println(lightValue);          // Print value to the Serial Monitor
  
  delay(500);                          // Wait for half a second between readings
}
