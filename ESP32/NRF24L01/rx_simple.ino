#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

/* Variables */
RF24 radio(5, 6);  // CE, CSN
const byte address[6] = "1207";

/* My Functions */
void setupNRF24L01() {
  radio.begin();
  if (radio.isChipConnected())
    Serial.println("NRF24L01 OK");
  else {
    Serial.println("NRF24L01 FAIL");
    while (true)
      ;
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX, 1);
  delay(1000);
  if (radio.setDataRate(RF24_250KBPS))
    Serial.println("setDataRate OK");
  else
    Serial.println("setDataRate FAIL");
  radio.startListening();
  delay(1000);
}

/* Main Function */
void setup() {
  Serial.begin(115200);
  // NRF24L01
  setupNRF24L01();
}

void loop() {
  bool goodSignal = radio.testRPD();
  if (radio.available()) {
    // Test signal
    Serial.println(goodSignal ? "Strong > -64dBm" : "Weak < -64dBm");
    // Data
    char text[100] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    if ((strcmp(text, "Hello") == 0)) {
      Serial.println("Nice!");
    }
  }
}
