#define sensor 7
#define LED 2

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Code written by sensorvn.com");
  delay(1000);
  pinMode(sensor, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(sensor, LOW);
}
void loop() {
  if (digitalRead(sensor)) {
    Serial.println("Movement detected.");
    digitalWrite(LED, HIGH);
  } else {
    Serial.println("Did not detect movement.");
    digitalWrite(LED, LOW);
  }
  delay(100);
}
