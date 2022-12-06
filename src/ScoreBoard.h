#ifndef SNAKE_SCOREBOARD
#define SNAKE_SCOREBOARD

#include <Adafruit_SPITFT.h>
#include "Point.h"

class ScoreBoard
{
public:
    ScoreBoard(Point _origin, int width, int height);
    void Initialize();
    void DrawInitial(Adafruit_SPITFT* display);
    void DrawUpdate(Adafruit_SPITFT* display);
    int GetScore();
    int IncreaseScore(int increaseAmount);
    float GetTime();
private:

    Point _origin;
    int _width;
    int _height;
    int _score;
    bool _scoreChanged = true;
    uint32_t _startTime;
};

#endif