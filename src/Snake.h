#ifndef SNAKE_SNAKE
#define SNAKE_SNAKE

#include "Common.h"
#include "Point.h"
#include "Segment.h"
#include <vector>
#include <Adafruit_SPITFT.h>

class Snake
{
public:
  Snake() = default;
  
  void Initialize(Point p, Direction dir, int maxLength, int segmentWidth, int segmentHeight);
  void TurnSnake(Rotation rotation);
  void UpdateSnake();
  bool IsSnakeEatingItself();
  bool IsSnakeIntersecting(Segment segment);
  int IncreaseLength(int length);
  Segment GetHead();
  std::vector<Segment>& GetSegments();

  void DrawSnake(Adafruit_SPITFT* display);
  void ClearSnakeTail(Adafruit_SPITFT* display);
  void DrawSnakeUpdate(Adafruit_SPITFT* display);
private:
  volatile Direction _pendingDirection = Direction::Unset;
  size_t _maxLength;
  Direction _direction = Direction::Unset;
  std::vector<Segment> _segments;
  std::vector<Segment> _removedSegments;
};

#endif