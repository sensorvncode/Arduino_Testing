void setup() {
  Serial.begin(9600);   // Khởi động UART với baud rate là 9600
}

void loop() {
  static String receivedString = "";  // Biến để lưu trữ chuỗi nhận được
  while (Serial.available() > 0) {  // Đọc và xử lý tất cả dữ liệu có sẵn trong buffer
    char receivedChar = Serial.read();  // Đọc ký tự từ UART
    receivedString += receivedChar;  // Nối ký tự vào chuỗi nhận được
  }
  
  // Kiểm tra nếu nhận được ký tự kết thúc (ví dụ '\n')
  if (receivedString.endsWith("\n")) {
    receivedString.trim();  // Xóa khoảng trắng ở đầu và cuối chuỗi
    Serial.print("Received: ");
    Serial.println(receivedString);  // In ra chuỗi nhận được
    receivedString = "";  // Đặt lại chuỗi nhận được để nhận dữ liệu tiếp theo
  }
}
