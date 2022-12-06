#ifndef SNAKE_GAMEBOARD
#define SNAKE_GAMEBOARD

#include <Adafruit_SPITFT.h>
#include "Snake.h"
#include "ScoreBoard.h"
#include "Common.h"
#include "Treat.h"

const int SpaceSize = 8;
enum class GameState
{
  InPlay = 0,
  GameOverScreen = 1
};

class GameBoard
{
public:
  GameBoard(Point origin, int width, int height, Snake& snake, ScoreBoard& scoreBoard, int leftPin, int rightPin);
  void Initialize(Adafruit_SPITFT* display);

  void Update();
  Treat GetActiveTreat();

private:
  bool IntersectingBoarder(Segment s);
  void InitializeInternal();
  
  Adafruit_SPITFT* _display;

  Point _origin;
  int _width;
  int _height;

  Treat _activeTreat = { };
  Snake& _snake;
  ScoreBoard& _scoreBoard;

  int _leftPin;
  int _rightPin;

  GameState _state = GameState::InPlay;

  uint32_t _frameCounter = 0;
  uint32_t _lastFrameButtonPressed = 0;
};

#endif