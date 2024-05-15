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
  printLcd("ST7735 OK");
  delay(200);
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

/* Main Function */
void setup(void) {
  // TFT 1.44
  setupST7735();
  printLcdAxis(0, 12, "Le Xuan Khanh", ST77XX_YELLOW);
}

void loop() {
}
