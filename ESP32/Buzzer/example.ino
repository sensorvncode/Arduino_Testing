/* Variables */
// Chân kết nối với buzzer
#define buzzerPin 52
// Các tần số của các nốt nhạc
#define note_C 261
#define note_D 293
#define note_E 329
#define note_F 349
#define note_G 392
#define note_A 440
#define note_B 493
// Nhịp độ (delay giữa các nốt nhạc)
int tempo = 400;  // Tốc độ nhịp của bài hát (ms giữa các nốt)

/* Main Functions */
void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Bài hát Do-Re-Mi (với tần số và nhịp độ đơn giản)
  // Do
  tone(buzzerPin, note_C);
  delay(tempo);
  noTone(buzzerPin);  // Ngưng tạo xung

  // Re
  tone(buzzerPin, note_D);
  delay(tempo);
  noTone(buzzerPin);

  // Mi
  tone(buzzerPin, note_E);
  delay(tempo);
  noTone(buzzerPin);

  // Fa
  tone(buzzerPin, note_F);
  delay(tempo);
  noTone(buzzerPin);

  // Sol
  tone(buzzerPin, note_G);
  delay(tempo);
  noTone(buzzerPin);

  // La
  tone(buzzerPin, note_A);
  delay(tempo);
  noTone(buzzerPin);

  // Si
  tone(buzzerPin, note_B);
  delay(tempo);
  noTone(buzzerPin);

  // Lặp lại từ đầu
  digitalWrite(buzzerPin, HIGH);  // Tắt
  delay(1000);                    // Thời gian nghỉ giữa các vòng chơi
}
