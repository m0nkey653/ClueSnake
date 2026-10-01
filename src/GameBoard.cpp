#include "GameBoard.h"
#include "Colors.h"
#include "Segment.h"
#include "GameOverScreen.h"

const int SnakeSegmentWidth = 5;
const int SnakeSegmentHeight = 2;
const int TreatSize = 6;
const int MaxScore = 10;
const int SnakeStartLength = 60;
const int SnakeIncreaseLength = 60;
const int ButtonPressDebounce = 3;


volatile Rotation rotationPress = Rotation::None;

void ButtonLeftPress() {
  if (rotationPress == Rotation::None) {
    rotationPress = Rotation::Left;
  }
}

void ButtonRightPress() {
  if (rotationPress == Rotation::None) {
    rotationPress = Rotation::Right;
  }
}

GameBoard::GameBoard(Point origin, int width, int height, Snake& snake, ScoreBoard& scoreBoard, int leftPin, int rightPin)
    : _origin(origin),
    _width(width),
    _height(height),
    _snake(snake),
    _scoreBoard(scoreBoard),
    _leftPin(leftPin),
    _rightPin(rightPin)
{ }

void GameBoard::Initialize(Adafruit_SPITFT* display)
{
    Serial.println("GameBoard::Initialize - Start");
    _display = display;
    
    attachInterrupt(digitalPinToInterrupt(_leftPin), ButtonLeftPress, FALLING);
    attachInterrupt(digitalPinToInterrupt(_rightPin), ButtonRightPress, FALLING);

    InitializeInternal();

    Serial.println("GameBoard::Initialize - End");
    
}

void GameBoard::InitializeInternal()
{
    _scoreBoard.Initialize();
    _scoreBoard.DrawInitial(_display);

    _display->fillRect(_origin._x, _origin._y, _width, _height, ARCADA_BLACK);

    for (int i = 0; i < SpaceSize - 1; i++)
    {
        _display->drawRect(_origin._x + i, _origin._y + i, _width - 2*i, _height - 2*i, ARCADA_WHITE);
    }

    _snake.Initialize(Point(100, 100), Direction::East, SnakeStartLength, SnakeSegmentWidth, SnakeSegmentHeight);

    _activeTreat = GetActiveTreat();
    _activeTreat.Draw(_display);
    
    _snake.DrawSnake(_display);
  
  
    rotationPress = Rotation::None;
    _frameCounter = 0;
    _lastFrameButtonPressed = 0;

    _state = GameState::InPlay;
}

void GameBoard::Update()
{
    if (_state == GameState::InPlay)
    {   
        _frameCounter++;
        if (rotationPress != Rotation::None)
        {
            if (_frameCounter - _lastFrameButtonPressed > ButtonPressDebounce)
            {
                _snake.TurnSnake(rotationPress);
                _lastFrameButtonPressed = _frameCounter;
            }
            rotationPress = Rotation::None;
        }

        _snake.UpdateSnake();
        _snake.ClearSnakeTail(_display);
        _snake.DrawSnake(_display);

        if (_activeTreat.SegmentIntersects(_snake.GetHead()))
        {
            _activeTreat.Clear(_display, _snake.GetHead());

            auto currentScore = _scoreBoard.IncreaseScore(1);
            if (currentScore >= MaxScore)
            {
                _state = GameState::GameOverScreen;
            }
            else
            {
                //_activeTreat.SerialPrint("Treat eaten: ");
                _snake.IncreaseLength(SnakeIncreaseLength);
                _activeTreat = GetActiveTreat();
                //_activeTreat.SerialPrint("New Active Treat: ");
                _activeTreat.Draw(_display);
            }
        }
        if (_snake.IsSnakeEatingItself())
        {
            _state = GameState::GameOverScreen;
        }
        if (IntersectingBorder(_snake.GetHead()))
        {
            _state = GameState::GameOverScreen;
        }

        _scoreBoard.DrawUpdate(_display);
    }
    
    if (_state == GameState::GameOverScreen)
    {
        int score = _scoreBoard.GetScore();
        String gameOverText = (score >= MaxScore) ? "  You Win!  " : "Game Over :(";
        GameOverScreen gos;

        gos.Initialize(_display, gameOverText, _origin, 240, 200, score, _scoreBoard.GetTime());
        do
        {
            delay(50);
        }
        while (rotationPress == Rotation::None);
        
        InitializeInternal();
    }
}

Treat GameBoard::GetActiveTreat()
{
    Point activeTreatPoint = {};
    Treat activeTreat = {};
    do
    {
        activeTreatPoint._x = (char)random(_origin._x + SpaceSize, _width - SpaceSize - TreatSize);
        activeTreatPoint._y = (char)random(_origin._y + SpaceSize, _height - SpaceSize - TreatSize);
        Treat t(activeTreatPoint, TreatSize, ARCADA_RED);
        activeTreat = t;
    }
    while (activeTreat.SegmentIntersects(_snake.GetSegments()));
    return activeTreat;
}

bool GameBoard::IntersectingBorder(Segment s)
{
    int leftBorder = _origin._x + SpaceSize;
    if (s._topLeft._x <= leftBorder)
    {
        return true;
    }
    int topBorder = _origin._y + SpaceSize;
    if (s._topLeft._y <= topBorder)
    {
        return true;
    }
    int rightBorder = _origin._x + _width - SpaceSize;
    if (s._bottomRight._x >= rightBorder)
    {
        return true;
    }
    int bottomBorder = _origin._y + _height - SpaceSize;
    if (s._bottomRight._y >= bottomBorder)
    {
        return true;
    }
    return false;
}