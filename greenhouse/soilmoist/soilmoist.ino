const int sensorPin = A0; // Analog pin connected to sensor AOUT
int moistureValue = 0;    // Variable to store the incoming reading

void setup() {
  Serial.begin(9600);     // Initialize serial communication at 9600 baud
  Serial.println("HW-080 Soil Sensor Initialized");
}

void loop() {
  moistureValue = analogRead(sensorPin); // Read the analog value from the sensor
  
  Serial.print("Moisture Raw Value: ");
  Serial.println(moistureValue);         // Print the raw ADC value (0-1023)
  
  delay(1000);                           // Wait 1 second between readings
}
