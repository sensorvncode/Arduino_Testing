String incomingData = "";  // Biến để lưu trữ dữ liệu nhận được

void setup() {
  Serial.begin(9600);  // Khởi động cổng serial với baud rate là 9600 bps
}

void loop() {
  if (Serial.available() > 0) {
    // Đọc dữ liệu vào chuỗi incomingData
    incomingData = Serial.readStringUntil('\n');  // Đọc đến khi gặp ký tự xuống dòng '\n'
    // In ra dữ liệu chỉ khi nhận được dữ liệu mới
    if (incomingData != "") {
      Serial.print("I received: ");
      Serial.println(incomingData);
      incomingData = "";                // Đặt lại chuỗi nhận được để chuẩn bị nhận dữ liệu mới
      delay(10);                        // Đợi một chút để xử lý hoàn tất việc gửi và nhận dữ liệu
      while (Serial.available() > 0) {  // Xóa bộ đệm Serial
        char junk = Serial.read();
      }
    }
  }
}
