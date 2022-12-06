#include "GameOverScreen.h"
#include "Colors.h"
#include "Fonts/FreeSerifBold18pt7b.h"
#include "Fonts/FreeSerifBold12pt7b.h"
#include "Fonts/FreeSans12pt7b.h"

void GameOverScreen::Initialize(Adafruit_SPITFT* display, String gameOverText, Point origin, int screenWidth, int screenHeight, int _score, float _time)
{
    int boundarySize = 20;
    Point topLeft = { origin._x + boundarySize, origin._y + boundarySize };
    int panelWidth = screenWidth - (boundarySize * 2);
    int panelHeight = screenHeight - (boundarySize * 2);
    display->fillRoundRect(topLeft._x, topLeft._y, panelWidth, panelHeight, 10, ARCADA_DARKGREY);
    display->fillRoundRect(topLeft._x + 5, topLeft._y + 5, panelWidth - 10, panelHeight - 10, 10, ARCADA_WHITE);

    Point gameOverTextCursor = { origin._x + 45, origin._y + 50};
    display->setCursor(gameOverTextCursor._x, gameOverTextCursor._y);
    display->setTextColor(ARCADA_DARKGREEN);
    display->setFont(&FreeSerifBold12pt7b);
    display->print(gameOverText);

    Point scoreTextCursor = { origin._x + 60, origin._y + 100};
    display->setCursor(scoreTextCursor._x, scoreTextCursor._y);
    display->setTextColor(ARCADA_DARKGREEN);
    display->setFont(&FreeSans12pt7b);
    display->printf("Score: %d", _score);

    Point timeTextCursor = { origin._x + 50, origin._y + 130};
    display->setCursor(timeTextCursor._x, timeTextCursor._y);
    display->setTextColor(ARCADA_DARKGREEN);
    display->setFont(&FreeSans12pt7b);
    display->printf(" Time: %.2f", _time);
}