#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <Ethernet.h>

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
  testdrawtext("ST7735 OK", ST77XX_WHITE);
  delay(2000);
  tft.fillScreen(ST77XX_BLACK);
}
void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

/* Main Function */
void setup(void) {
  // TFT 1.44
  setupST7735();
}

void loop() {
}
