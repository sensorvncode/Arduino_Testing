#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

/* Variables */
// For 1.44" with ST7735 use:
#define TFT_CS 17
#define TFT_RST 26
#define TFT_DC 25  // RS
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

/* My Function */
void setupST7735() {
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  printLCD("ST7735 OK");
}
void testdrawtext(char *text, uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
void printLCD(char *text) {
  testdrawtext(text, ST77XX_WHITE);
}

/* Main Function */
void setup(void) {
  // TFT 1.44
  setupST7735();
}

void loop() {
}
