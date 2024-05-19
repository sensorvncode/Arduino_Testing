#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* Variables */
RF24 radio(4, 5);  // CE, CSN
const byte address[6] = "1207";
#define LED 2

/* My Functions */
void printLCD(const char* data) {
  lcd.setCursor(0, 0);
  lcd.print(data);
}

/* Main Function */
void setup() {
  // Serial
  lcd.init();
  lcd.backlight();
  // NRF24L01
  radio.begin();
  if (radio.isChipConnected())
    printLCD("NRF24L01 OK");
  else {
    printLCD("NRF24L01 FAIL");
    while (true)
      ;
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX, 1);
  delay(1000);
  if (radio.setDataRate(RF24_250KBPS))
    printLCD("setDataRate OK");
  else
    printLCD("setDataRate FAIL");
  radio.startListening();
  delay(1000);
  // LED
  pinMode(LED, OUTPUT);
}

void loop() {
  bool goodSignal = radio.testRPD();
  if (radio.available()) {
    lcd.clear();
    // Test signal
    printLCD(goodSignal ? "Strong > -64dBm" : "Weak < -64dBm");
    // Data
    char text[3] = "";
    radio.read(&text, sizeof(text));
    lcd.setCursor(0, 1);
    lcd.print(text);
    if (strcmp(text, "On") == 0)
      digitalWrite(LED, HIGH);
    else
      digitalWrite(LED, LOW);
  }
}
