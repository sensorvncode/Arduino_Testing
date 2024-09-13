/* Variables */
// joystick pins
const int SWITCH = 0;  // digital pin 2 connected to SW output of JoyStick
const int X_AX = A1;   // analog pin 0 connected to X output of JoyStick
const int Y_AX = A0;   // analog pin 1 connected to Y output of JoyStick
int rows = 0;

/* My Function */
void showHeading() {
  Serial.println("Switch      X axis      Y axis");
}

/* Main Functions */
void setup() {
  Serial.begin(115200);
  pinMode(SWITCH, INPUT);
  digitalWrite(SWITCH, HIGH);

  showHeading();
}
void loop() {
  rows++;
  if (rows > 20) {
    rows = 0;
    showHeading();
  }
  Serial.print(digitalRead(SWITCH));
  Serial.print("          ");
  Serial.print(analogRead(X_AX));
  Serial.print("          ");
  Serial.println(analogRead(Y_AX));
  delay(100);  // delay in between reads for stability
}
