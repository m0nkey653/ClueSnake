#ifndef SNAKE_POINT
#define SNAKE_POINT

#include <Arduino.h>
#include "Common.h"

struct Point
{
  Point() {}
  Point (int x, int y) : _x(x), _y(y) {}
  int _x = 0;
  int _y = 0;

  Point NextPoint(Direction dir)
  {
    switch (dir)
    {
      case Direction::North:
        return Point(_x, _y - 1);
      case Direction::East:
        return Point(_x + 1, _y);
      case Direction::South:
        return Point(_x, _y + 1);
      case Direction::West:
        return Point(_x - 1, _y);
      default:
        return Point(_x, _y);
    }
  }

  bool operator==(const Point& rhs)
  {
      return (_x == rhs._x && _y == rhs._y)
        || (_x + 1 == rhs._x && _y == rhs._y)
        || (_x == rhs._x && _y + 1 == rhs._y)
        || (_x + 1 == rhs._x && _y + 1 == rhs._y);
  }
};

#endif