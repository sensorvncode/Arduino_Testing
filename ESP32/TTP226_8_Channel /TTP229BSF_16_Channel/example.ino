/*
  Created by SENSORVN.COM, February 19, 2024.
*/
/* Variables */
#define SDO_ 2
#define SCL_ 3
volatile bool flag = 0;
volatile byte flag2 = 0;
byte data_ = 0;
byte data = 0;

/* Arduino Function */
void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
  pinMode(SCL_, OUTPUT);
  pinMode(SDO_, INPUT);
  digitalWrite(SCL_, HIGH);
  attachInterrupt(digitalPinToInterrupt(SDO_), handleInterrupt, FALLING);
  // Calibration
  Serial.print("Calibrating Sensor .................. ");
  delay(4000);
  Serial.println("Done");
}
void loop() {
  if (flag == 1) {
    work();
  }
}

/* Function */
void delaySensor() {
  for (int i = 0; i < 50; i++) {
    if (!digitalRead(SDO_)) {
      if (flag2 == 0) {
        data = data_;
        flag2++;
      }
      if (flag2 == 1) {
        Serial.println(data);
        flag2++;
      }
    }
  }
}
void work() {
  for (int i = 1; i < 17; i++) {
    data_ = i;
    digitalWrite(SCL_, LOW);
    delaySensor();
    digitalWrite(SCL_, HIGH);
    delaySensor();
  }
  flag2 = 0;
  flag = 0;
  delay(500);
  attachInterrupt(digitalPinToInterrupt(SDO_), handleInterrupt, FALLING);
}
void handleInterrupt() {
  flag = 1;
  detachInterrupt(digitalPinToInterrupt(SDO_));
}
