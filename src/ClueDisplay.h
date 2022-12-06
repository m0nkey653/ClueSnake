#ifndef CLUE_DISPLAY
#define CLUE_DISPLAY

#include <Adafruit_ST7789.h>

#define ARCADA_TFT_SPI SPI1
#define ARCADA_TFT_CS 31  // Display CS Arduino pin number
#define ARCADA_TFT_DC 32  // Display D/C Arduino pin number
#define ARCADA_TFT_RST 33 // Display reset done with chip
#define ARCADA_TFT_LITE 34
#define ARCADA_TFT_ROTATION 1
#define ARCADA_TFT_DEFAULTFILL 0x0
#define ARCADA_TFT_WIDTH 240
#define ARCADA_TFT_HEIGHT 240

class ClueDisplay
{
public:
    void BeginDisplay(void);
    Adafruit_ST7789* GetDisplay();
    void SetBackLight(short brightness);
private:
    Adafruit_ST7789* _display;
};

#endif