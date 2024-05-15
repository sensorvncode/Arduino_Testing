#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/* Variables */
RF24 radio(4, 5);  // CE, CSN
const byte address[6] = "1207";
#define LED 2

/* Main Function */
void setup() {
  // Serial
  Serial.begin(9600);
  // NRF24L01
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
  radio.startListening();
  delay(2000);
  // LED
  pinMode(LED, OUTPUT);
}

void loop() {
  if (radio.available()) {
    char text[3] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    if (strcmp(text, "On") == 0)
      digitalWrite(LED, HIGH);
    else
      digitalWrite(LED, LOW);
  }
}
