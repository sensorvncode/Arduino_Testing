const int analogPin = A0;    // Pin connected to OUT of ACS712
const int sensorZero = 512;  // Midpoint value (2.5V) for 10-bit ADC with 5V reference

float sensitivity = 0.185;  // Sensitivity for ACS712-05B is 185 mV/A

void setup() {
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  int sensorValue = analogRead(analogPin);       // Read the analog input
  float voltage = (sensorValue / 1024.0) * 5.0;  // Convert ADC value to voltage

  // Calculate current (adjust the voltage offset as needed)
  float current = (voltage - 2.5) / sensitivity;

  // Print the results
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print("  Voltage: ");
  Serial.print(voltage);
  Serial.print(" V  Current: ");
  Serial.print(current);
  Serial.println(" A");

  delay(1000);  // Wait for a second before taking another reading
}
