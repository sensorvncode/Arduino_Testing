#define RED 10
#define GREEN 11
#define BLUE 9

void setup() {
  for (int i = 9; i <= 11; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  checkRGB(1000);
}

void checkRGB(int time) {
  // RED
  analogWrite(RED, 255);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  delay(time);
  // GREEN
  analogWrite(RED, 0);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 0);
  delay(time);
  // BLUE
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 255);
  delay(time);
  // WHITE
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
  delay(time);
  // YELLOW
  analogWrite(RED, 255);
  analogWrite(GREEN, 17);
  analogWrite(BLUE, 0);
  delay(time);
  // Cyan
  analogWrite(RED, 0);
  analogWrite(GREEN, 17);
  analogWrite(BLUE, 50);
  delay(time);
  // Magenta
  analogWrite(RED, 255);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 17);
  delay(time);
}
