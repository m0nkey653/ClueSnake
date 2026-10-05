#include "ImageLoader.h"
#include "ClueDisplay.h"
#include "Colors.h"

Adafruit_FlashTransport_QSPI flashTransport;
Adafruit_SPIFlash flash(&flashTransport);
FatFileSystem filesys;
Adafruit_ImageReader reader(filesys);

volatile bool ImageLoaderDisplayRelease = false;
void ImageLoaderRelease()
{
    Serial.println("ImageLoader::ImageLoaderRelease");
    ImageLoaderDisplayRelease = true;
}

ImageLoader::ImageLoader() {}

void ImageLoader::Setup(Adafruit_SPITFT *display)
{
    _display = display;
    if (!flash.begin())
    {
        Serial.println("Error, failed to initialize flash chip! Images will be skipped.");
        return;
    }
    if (!filesys.begin(&flash))
    {
        Serial.println("Error, failed to mount filesystem! Images will be skipped.");
        Serial.println("Was the flash chip formatted with the SdFat_format example?");
        return;
    }
    _filesystemReady = true;
}

ImageReturnCode ImageLoader::DisplayImage(const char *imagePath)
{
    /*
    IMAGE_SUCCESS — Image loaded successfully (or was clipped fully off screen, still considered “successful” in that there was no error).
    IMAGE_ERR_FILE_NOT_FOUND — Could not open the requested file (check spelling, confirm file actually exists on the card, make sure it conforms to “8.3” file naming convention (e.g. “filename.bmp”).
    IMAGE_ERR_FORMAT — Not a supported image format. Currently only uncompressed 24-bit color BMPs are supported (more will likely be added over time).
    IMAGE_ERR_MALLOC — Could not allocate memory for operation (drawBMP() won’t generate this error, but other ImageReader functions might).
    */
    if (!_filesystemReady)
    {
        // no filesystem means no images, treat it the same as a missing file
        return IMAGE_ERR_FILE_NOT_FOUND;
    }

    ImageReturnCode stat = reader.drawBMP(imagePath, *_display, 0, 0);
    if (stat != IMAGE_SUCCESS)
    {
        reader.printStatus(stat);

        // a missing image isn't worth an error screen, let the caller skip it
        if (stat == IMAGE_ERR_FILE_NOT_FOUND)
        {
            return stat;
        }

        auto resultString = GetStatusMessage(stat);

        _display->setCursor(0, 0);
        _display->setTextSize(3);
        _display->setTextColor(ARCADA_RED);
        _display->println("Error loading: " + String(imagePath));
        _display->println(resultString);
    }
    return stat;
}

void ImageLoader::DisplayImage(const char *imagePath, std::vector<int> releaseButtonPins)
{
    Serial.println("ImageLoader::DisplayImage - started");
    if (DisplayImage(imagePath) == IMAGE_ERR_FILE_NOT_FOUND)
    {
        Serial.println("ImageLoader::DisplayImage - image not found, skipping");
        return;
    }

    for (auto pin : releaseButtonPins)
    {
        int mask = attachInterrupt(digitalPinToInterrupt(pin), ImageLoaderRelease, FALLING);
        Serial.println("ImageLoader::DisplayImage - attachInterrupt - Pin: [" + String(pin) + "] Mask: [" + String(mask) + "]");
    }

    ImageLoaderDisplayRelease = false;
    
    Serial.println("ImageLoader::DisplayImage - awaiting keypress");
    while (!ImageLoaderDisplayRelease)
    {
        delay(50);
    }

    for (auto pin : releaseButtonPins)
    {
        detachInterrupt(digitalPinToInterrupt(pin));
        Serial.println("ImageLoader::DisplayImage - detachInterrupt - Pin: [" + String(pin) + "]");
    }
    
    Serial.println("ImageLoader::DisplayImage - ended");
}

String ImageLoader::GetStatusMessage(ImageReturnCode stat)
{
    if (stat == IMAGE_SUCCESS)
        return "Success!";
    else if (stat == IMAGE_ERR_FILE_NOT_FOUND)
        return "File not found.";
    else if (stat == IMAGE_ERR_FORMAT)
        return "Not a supported BMP variant.";
    else if (stat == IMAGE_ERR_MALLOC)
        return "Malloc failed (insufficient RAM).";
    
    return "Invalid Stat";
}