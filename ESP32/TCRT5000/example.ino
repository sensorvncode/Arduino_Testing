#define sensor 7
#define LED 2

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(sensor, LOW);
}
void loop() {
  if (digitalRead(sensor)) {
    Serial.println("Detected.");
    digitalWrite(LED, HIGH);
  } else {
    Serial.println("Did not detect.");
    digitalWrite(LED, LOW);
  }
  delay(100);
}
