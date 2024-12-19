// Chân kết nối với buzzer
const int buzzerPin = 52;

// Các tần số của các nốt nhạc
int note_C = 261;
int note_D = 293;
int note_E = 329;
int note_F = 349;
int note_G = 392;
int note_A = 440;
int note_B = 493;

// Nhịp độ (delay giữa các nốt nhạc)
int tempo = 400;  // Tốc độ nhịp của bài hát (ms giữa các nốt)

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Bài hát Do-Re-Mi (với tần số và nhịp độ đơn giản)
  // Do
  tone(buzzerPin, note_C);
  delay(tempo);
  noTone(buzzerPin);  // Dừng phát âm thanh

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
  digitalWrite(buzzerPin, HIGH);
  delay(1000);  // Thời gian nghỉ giữa các vòng chơi
}
