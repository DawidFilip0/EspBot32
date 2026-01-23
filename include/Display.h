#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <globals.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

class Display
{
    public:
        Display();
        void initDisplay();
        void displayArrow(int action);
        void clearDisplay();
        void displayText(String text, int16_t x, int16_t y, uint16_t color);
        
    private:
        Adafruit_ST7735 tft;
        
        void drawUpArrow(int16_t centerX, int16_t centerY, int size, uint16_t color);
        void drawDownArrow(int16_t centerX, int16_t centerY, int size, uint16_t color);
        void drawLeftArrow(int16_t centerX, int16_t centerY, int size, uint16_t color);
        void drawRightArrow(int16_t centerX, int16_t centerY, int size, uint16_t color);
        void drawRotatingLeftArrow(int16_t centerX, int16_t centerY, int size, uint16_t color);
        void drawRotatingRightArrow(int16_t centerX, int16_t centerY, int size, uint16_t color);
        void drawCrossroads(int16_t centerX, int16_t centerY, int size, uint16_t color);
        void drawRecovery(int16_t centerX, int16_t centerY, int size, uint16_t color);
};

#endif