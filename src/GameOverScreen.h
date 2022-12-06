#ifndef SNAKE_GAMEOVERSCREEN
#define SNAKE_GAMEOVERSCREEN

#include <Adafruit_SPITFT.h>
#include "Point.h"

class GameOverScreen
{
public:
    GameOverScreen() = default;
    void Initialize(Adafruit_SPITFT* display, String gameOverText, Point origin, int screenWidth, int screenHeight, int _score, float _time);
private:
};

#endif