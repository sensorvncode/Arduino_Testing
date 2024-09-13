#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/* Variables */
// NRF24L01
RF24 radio(5, 6);  // CE, CSN
const byte address[6] = "1207";

/* My Function */
void setupNRF24L01() {
  radio.begin();
  if (radio.isChipConnected())
    Serial.println("NRF24L01 OK");
  else {
    Serial.println("NRF24L01 FAIL");
    while (true)
      ;
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX, 1);
  delay(1000);
  if (radio.setDataRate(RF24_250KBPS))
    Serial.println("NRF24L01 setDataRate OK");
  else
    Serial.println("NRF24L01 setDataRate FAIL");
  radio.stopListening();
  delay(1000);
}

/* Main Function */
void setup(void) {
  Serial.begin(115200);
  // NRF24L01
  setupNRF24L01();
}

void loop() {
  // ON
  const char text[] = "Hello";
  if (radio.write(&text, sizeof(text)))
    Serial.println("Successfull ");
  else
    Serial.println("Failed or timed out");
  delay(10000);
  setupNRF24L01();
}
