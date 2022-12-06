#include "ClueDisplay.h"
#include <Arduino.h>

void ClueDisplay::BeginDisplay(void)
{
    Serial.println("CLUE display begin");

    Adafruit_ST7789 *tft = new Adafruit_ST7789(
        &ARCADA_TFT_SPI,
        ARCADA_TFT_CS,
        ARCADA_TFT_DC,
        ARCADA_TFT_RST);

    tft->init(240, 240);
    tft->setRotation(ARCADA_TFT_ROTATION);
    tft->fillScreen(ARCADA_TFT_DEFAULTFILL);
    uint8_t rtna = 0x01; // Screen refresh rate control (datasheet 9.2.18, FRCTRL2)
    tft->sendCommand(0xC6, &rtna, 1);
    _display = tft;

    for (int i = 0; i < 250; i += 10) {
        SetBackLight(i);
        delay(1);
    }
}

void ClueDisplay::SetBackLight(short brightness)
{
    analogWrite(ARCADA_TFT_LITE, brightness);
}

Adafruit_ST7789* ClueDisplay::GetDisplay()
{
    return _display;
}