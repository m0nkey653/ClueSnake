#ifndef SNAKE_COMMON
#define SNAKE_COMMON

#include <Arduino.h>

enum class Rotation
{
  None = -1,
  Left = 0,
  Right = 1,
};

// const char* RotationString(Rotation rotation)
// {
//   switch (rotation)
//   {
//     case Rotation::None:
//       return "Unset";
//     case Rotation::Left:
//       return "North";
//     case Rotation::Right:
//       return "East";
//     default:
//       return "Rotation::UNDEFINED";
//   }
// }

enum class Direction
{
  Unset = -1,
  North = 0,
  East = 1,
  South = 2,
  West = 3
};

// const char* DirectionString(Direction direction)
// {
//   switch (direction)
//   {
//     case Direction::Unset:
//       return "Unset";
//     case Direction::North:
//       return "North";
//     case Direction::East:
//       return "East";
//     case Direction::South:
//       return "South";
//     case Direction::West:
//       return "West";
//     default:
//       return "Direction::UNDEFINED";
//   }
// }

#endif