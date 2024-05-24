void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Read the analog input from pin A0
  int sensorValue = analogRead(A0);
  
  // Print the sensor value to the serial monitor
  Serial.print("Analog Input A0: ");
  Serial.println(sensorValue);

  // Add a delay to slow down the serial output (optional)
  delay(1000); // Wait for 1 second
}
