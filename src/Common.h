#ifndef SNAKE_COMMON
#define SNAKE_COMMON

#include <Arduino.h>

enum class Rotation
{
  None = -1,
  Left = 0,
  Right = 1,
};

enum class Direction
{
  Unset = -1,
  North = 0,
  East = 1,
  South = 2,
  West = 3
};

#endif