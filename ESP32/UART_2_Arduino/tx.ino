void setup() {
  Serial.begin(9600);   // Khởi động UART với baud rate là 9600
}

void loop() {
  Serial.println("Hello from Board 1!");  // Gửi dữ liệu đi
  delay(1000);  // Đợi 1 giây trước khi gửi lại
}
