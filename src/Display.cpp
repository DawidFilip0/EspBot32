#include <Display.h>

// Pin definitions
// #define TFT_CS 36
// #define TFT_DC 37
// #define TFT_RES 45 // RST
// #define TFT_SCL 39 // SCLK
// #define TFT_SDA 38 // MOSI

#define TFT_SCLK 39//18
#define TFT_MOSI 38//21
#define TFT_CS   36//5
#define TFT_DC   37//16
#define TFT_RST  45//17

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

Display::Display() : tft(TFT_CS, TFT_DC, TFT_RST) {}

void Display::initDisplay() {
  SPI.begin(TFT_SCLK, -1, TFT_MOSI);

  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, LOW);
  delay(50);
  digitalWrite(TFT_RST, HIGH);
  delay(50);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(GREEN);
  delay(pdMS_TO_TICKS(5000));
}

void Display::clearDisplay() {
  tft.fillScreen(BLACK);
}

void Display::displayText(String text, int16_t x, int16_t y, uint16_t color) {
  tft.setTextColor(color);
  tft.setTextSize(2);
  tft.setCursor(x, y);
  tft.println(text);
}

void Display::displayArrow(int action) {
  clearDisplay();
  
  int16_t centerX = tft.width() / 2;
  int16_t centerY = tft.height() / 2;
  int size = 30;
  
  switch(action) {
    case RECOVERY:
      drawRecovery(centerX, centerY, size, RED);
      displayText("RECOVERY", 30, 10, RED);
      break;
    case ROTATE_LEFT:
      drawRotatingLeftArrow(centerX, centerY, size, YELLOW);
      displayText("ROTATE LEFT", 20, 10, YELLOW);
      break;
    case TURN_LEFT:
      drawLeftArrow(centerX, centerY, size, GREEN);
      displayText("TURN LEFT", 25, 10, GREEN);
      break;
    case MOVE_FORWARD:
      drawUpArrow(centerX, centerY, size, CYAN);
      displayText("MOVE FORWARD", 15, 10, CYAN);
      break;
    case MOVE_BACKWARD:
      drawDownArrow(centerX, centerY, size, MAGENTA);
      displayText("MOVE BACKWARD", 10, 10, MAGENTA);
      break;
    case TURN_RIGHT:
      drawRightArrow(centerX, centerY, size, BLUE);
      displayText("TURN RIGHT", 20, 10, BLUE);
      break;
    case ROTATE_RIGHT:
      drawRotatingRightArrow(centerX, centerY, size, YELLOW);
      displayText("ROTATE RIGHT", 15, 10, YELLOW);
      break;
    case CROSSROAD:
      drawCrossroads(centerX, centerY, size, WHITE);
      displayText("CROSSROAD", 25, 10, WHITE);
      break;
    default:
      drawRecovery(centerX, centerY, size, RED);
      displayText("UNKNOWN", 30, 10, RED);
      break;
  }
}

void Display::drawUpArrow(int16_t centerX, int16_t centerY, int size, uint16_t color) {
  int16_t tipX = centerX;
  int16_t tipY = centerY - size;
  int16_t leftX = centerX - size / 2;
  int16_t rightX = centerX + size / 2;
  int16_t baseY = centerY + size;
  
  tft.drawLine(tipX, tipY, leftX, centerY, color);      // Left line
  tft.drawLine(tipX, tipY, rightX, centerY, color);     // Right line
  tft.drawLine(leftX, centerY, rightX, centerY, color); // Base line
  tft.drawLine(tipX, tipY, tipX, baseY, color);         // Shaft
}

void Display::drawDownArrow(int16_t centerX, int16_t centerY, int size, uint16_t color) {
  int16_t tipX = centerX;
  int16_t tipY = centerY + size;
  int16_t leftX = centerX - size / 2;
  int16_t rightX = centerX + size / 2;
  int16_t baseY = centerY - size;
  
  tft.drawLine(tipX, tipY, leftX, centerY, color);      // Left line
  tft.drawLine(tipX, tipY, rightX, centerY, color);     // Right line
  tft.drawLine(leftX, centerY, rightX, centerY, color); // Base line
  tft.drawLine(tipX, tipY, tipX, baseY, color);         // Shaft
}

void Display::drawLeftArrow(int16_t centerX, int16_t centerY, int size, uint16_t color) {
  int16_t tipX = centerX - size;
  int16_t tipY = centerY;
  int16_t topY = centerY - size / 2;
  int16_t bottomY = centerY + size / 2;
  int16_t baseX = centerX + size;
  
  tft.drawLine(tipX, tipY, centerX, topY, color);       // Top line
  tft.drawLine(tipX, tipY, centerX, bottomY, color);    // Bottom line
  tft.drawLine(centerX, topY, centerX, bottomY, color); // Base line
  tft.drawLine(tipX, tipY, baseX, tipY, color);         // Shaft
}

void Display::drawRightArrow(int16_t centerX, int16_t centerY, int size, uint16_t color) {
  int16_t tipX = centerX + size;
  int16_t tipY = centerY;
  int16_t topY = centerY - size / 2;
  int16_t bottomY = centerY + size / 2;
  int16_t baseX = centerX - size;
  
  tft.drawLine(tipX, tipY, centerX, topY, color);       // Top line
  tft.drawLine(tipX, tipY, centerX, bottomY, color);    // Bottom line
  tft.drawLine(centerX, topY, centerX, bottomY, color); // Base line
  tft.drawLine(tipX, tipY, baseX, tipY, color);         // Shaft
}

void Display::drawRotatingLeftArrow(int16_t centerX, int16_t centerY, int size, uint16_t color) {
  tft.drawCircle(centerX, centerY, size, color);
  tft.drawLine(centerX - size, centerY, centerX - size + 5, centerY - 10, color);
  tft.drawLine(centerX - size, centerY, centerX - size - 5, centerY - 10, color);
  tft.drawLine(centerX - size - 5, centerY - 10, centerX - size + 5, centerY - 10, color);
}

void Display::drawRotatingRightArrow(int16_t centerX, int16_t centerY, int size, uint16_t color) {
  tft.drawCircle(centerX, centerY, size, color);
  tft.drawLine(centerX + size, centerY, centerX + size + 5, centerY - 10, color);
  tft.drawLine(centerX + size, centerY, centerX + size - 5, centerY - 10, color);
  tft.drawLine(centerX + size + 5, centerY - 10, centerX + size - 5, centerY - 10, color);
}

void Display::drawCrossroads(int16_t centerX, int16_t centerY, int size, uint16_t color) {
  int arrowSize = size / 2;
  
  tft.drawLine(centerX, centerY - size, centerX, centerY - arrowSize, color);
  tft.drawLine(centerX, centerY - size, centerX - 5, centerY - size + 8, color);
  tft.drawLine(centerX, centerY - size, centerX + 5, centerY - size + 8, color);
  
  tft.drawLine(centerX, centerY + size, centerX, centerY + arrowSize, color);
  tft.drawLine(centerX, centerY + size, centerX - 5, centerY + size - 8, color);
  tft.drawLine(centerX, centerY + size, centerX + 5, centerY + size - 8, color);
  
  tft.drawLine(centerX - size, centerY, centerX - arrowSize, centerY, color);
  tft.drawLine(centerX - size, centerY, centerX - size + 8, centerY - 5, color);
  tft.drawLine(centerX - size, centerY, centerX - size + 8, centerY + 5, color);
  
  tft.drawLine(centerX + size, centerY, centerX + arrowSize, centerY, color);
  tft.drawLine(centerX + size, centerY, centerX + size - 8, centerY - 5, color);
  tft.drawLine(centerX + size, centerY, centerX + size - 8, centerY + 5, color);
  
  tft.drawCircle(centerX, centerY, 5, color);
}

void Display::drawRecovery(int16_t centerX, int16_t centerY, int size, uint16_t color) {
  tft.drawLine(centerX - size, centerY - size, centerX + size, centerY + size, color);
  tft.drawLine(centerX - size, centerY + size, centerX + size, centerY - size, color);
  tft.drawCircle(centerX, centerY, size + 5, color);
}