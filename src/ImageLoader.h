#ifndef CLUE_IMAGELOADER
#define CLUE_IMAGELOADER

// https://learn.adafruit.com/adafruit-gfx-graphics-library/loading-images

#include <SdFat.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_ImageReader.h>
#include <vector>


class ImageLoader
{
public:
    ImageLoader();
    void Setup(Adafruit_SPITFT *_display);
    void DisplayImage(const char *imagePath);
    void DisplayImage(const char *imagePath, std::vector<int> releaseButtonPins);
    String GetStatusMessage(ImageReturnCode stat);

private:
    Adafruit_SPITFT *_display;
};

#endif