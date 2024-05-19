#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/* Variables */
// For 1.44" with ST7735 use:
#define TFT_CS 17
#define TFT_RST 26
#define TFT_DC 25  // RS
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
// NRF24L01
RF24 radio(27, 14);  // CE, CSN
const byte address[6] = "1207";

/* My Function */
void setupST7735() {
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  printLcd("ST7735 OK");
  delay(2000);
}
void printLcdAxis(int x, int y, char *text, uint16_t color) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
void printLcd(char *text) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.print(text);
}
void setupNRF24L01() {
  radio.begin();
  if (radio.isChipConnected())
    printLcd("NRF24L01 OK");
  else {
    printLcd("NRF24L01 FAIL");
    while (true)
      ;
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX, 1);
  delay(1000);
  if (radio.setDataRate(RF24_250KBPS))
    printLcd("NRF24L01 setDataRate OK");
  else
    printLcd("NRF24L01 setDataRate FAIL");
  radio.stopListening();
  delay(1000);
}

/* Main Function */
void setup(void) {
  // TFT 1.44
  setupST7735();
  // NRF24L01
  setupNRF24L01();
}

void loop() {
  // ON
  const char text[] = "On";
  if (radio.write(&text, sizeof(text)))
    printLcd("Successfull ");
  else
    printLcd("Failed or timed out");
  printLcdAxis(0, 18, "Turn on", ST77XX_GREEN);
  delay(5000);
  setupNRF24L01();
  // OFF
  const char text2[] = "Off";
  if (radio.write(&text2, sizeof(text2)))
    printLcd("Successfull ");
  else
    printLcd("Failed or timed out");
  printLcdAxis(0, 18, "Turn off", ST77XX_RED);
  delay(5000);
  setupNRF24L01();
}
