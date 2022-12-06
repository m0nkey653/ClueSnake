#include "ScoreBoard.h"
#include "Colors.h"
#include "Fonts/FreeSerifBoldItalic12pt7b.h"

ScoreBoard::ScoreBoard(Point origin, int width, int height)
    : _origin(origin), _width(width), _height(height)
{
}

void ScoreBoard::Initialize()
{
    _startTime = millis();
    _score = 0;
}

void ScoreBoard::DrawInitial(Adafruit_SPITFT* display)
{
    display->drawRect(_origin._x, _origin._y, _width, _height, ARCADA_BLUE);
    display->drawRect(_origin._x + 1, _origin._y + 1, _width - 2, _height - 2, ARCADA_BLUE);
    display->fillRect(_origin._x + 2, _origin._y + 2, _width - 4, _height - 4, ARCADA_BLACK);

    display->setFont(&FreeSerifBoldItalic12pt7b);
    display->setCursor(_origin._x + 10, _origin._y + 27);
    display->setTextColor(ARCADA_GREENYELLOW);
    display->print("Snake!");
}

void ScoreBoard::DrawUpdate(Adafruit_SPITFT* display)
{
    //only clear the right halff
    display->fillRect(_origin._x + (_width / 2) + 2, _origin._y + 2, (_width / 2) - 4, _height - 4, ARCADA_BLACK);

    display->setTextWrap(false);
    display->setTextSize(1);
    display->setFont();

    display->setCursor(_origin._x + 150, _origin._y + 10);
    display->printf(" Time: %.2f", GetTime());

    display->setCursor(_origin._x + 150, _origin._y + 23);
    display->printf("Score: %d", _score);
}

float ScoreBoard::GetTime()
{
    uint32_t elapsed = millis() - _startTime;

    float time = static_cast<float>(elapsed) / (float)1000;
    return time;
}

int ScoreBoard::GetScore()
{
    return _score;
}

int ScoreBoard::IncreaseScore(int increaseAmount)
{
    _score += increaseAmount;
    return _score;
}