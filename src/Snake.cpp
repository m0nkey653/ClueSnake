#include "Snake.h"
#include "Segment.h"
#include "Common.h"
#include "Colors.h"

void Snake::Initialize(Point p, Direction dir, int maxLength, int segmentWidth, int segmentHeight)
{
  _direction = dir;
  _pendingDirection = Direction::Unset;
  _segments.clear();
  _segments.push_back(Segment(p, ARCADA_GREEN, dir, segmentWidth, segmentHeight));
  _maxLength = maxLength;
}

void Snake::TurnSnake(Rotation rotation)
{
  if (_pendingDirection != Direction::Unset || rotation == Rotation::None)
  {
    return;
  }
  
  switch (_direction)
  {
    case Direction::North:
      if (rotation == Rotation::Right) { _pendingDirection = Direction::East; }
      else if (rotation == Rotation::Left) { _pendingDirection = Direction::West; }
      break;
    case Direction::East:
      if (rotation == Rotation::Right) { _pendingDirection = Direction::South; }
      else if (rotation == Rotation::Left) { _pendingDirection = Direction::North; }
      break;
    case Direction::South:
      if (rotation == Rotation::Right) { _pendingDirection = Direction::West; }
      else if (rotation == Rotation::Left) { _pendingDirection = Direction::East; }
      break;
    case Direction::West:
      if (rotation == Rotation::Right) { _pendingDirection = Direction::North; }
      else if (rotation == Rotation::Left) { _pendingDirection = Direction::South; }
      break;
    default:
      break;
  }
  
  // Serial.printf("Snake::TurnSnake - CurrentDirection[%s] RotationInput[%s] PendingDirection[%s]\n",
  //   DirectionString(_direction), RotationString(rotation), DirectionString(_pendingDirection));
}

void Snake::UpdateSnake()
{
  if (_pendingDirection != Direction::Unset) { _direction = _pendingDirection; }
  Segment nextSegment = GetHead().GetNext(_direction);
  _segments.insert(_segments.begin(), nextSegment);

  while (_segments.size() > _maxLength)
  {
    _removedSegments.push_back(_segments.back());
    _segments.pop_back();
  }

  _pendingDirection = Direction::Unset;
}

String getDir(Direction d)
{
  if (d == Direction::North)
    return "N";
  if (d == Direction::East)
    return "E";
  if (d == Direction::West)
    return "W";
  if (d == Direction::South)
    return "S";
  
  return "U";
}

bool Snake::IsSnakeEatingItself()
{
  auto head = _segments[0];
  for (size_t i = 15; i < _segments.size(); i++)
  {
    if (head.Intersects(_segments[i]))
    {
      Serial.printf("Intersection at [%d] of [%d]\n", i, _segments.size());
      Serial.printf(" Head: (%d, %d) (%d, %d)\n", head._topLeft._x, head._topLeft._y, head._topRight._x, head._topRight._y);
      Serial.printf("       (%d, %d) (%d, %d)\n", head._bottomLeft._x, head._bottomLeft._y, head._bottomRight._x, head._bottomRight._y);

      for (size_t j = 1; j <= i; j++)
      {
        auto seg = _segments[j];
        Serial.printf("  Int[%d]: (%d, %d) (%d, %d)\n", j, seg._topLeft._x, seg._topLeft._y, seg._topRight._x, seg._topRight._y);
        Serial.printf("     [%s]: (%d, %d) (%d, %d)\n", getDir(seg._direction).c_str(), seg._bottomLeft._x, seg._bottomLeft._y, seg._bottomRight._x, seg._bottomRight._y);
        //Serial.printf("         %s", seg._)
      }
      return true;
    }
  }
  return false;
}

bool Snake::IsSnakeIntersecting(Segment segment)
{
  for (auto s : _segments)
  {
    if (s.Intersects(segment))
    {
      return true;
    }
  }
  return false;
}

int Snake::IncreaseLength(int length)
{
  _maxLength += length;
  return _maxLength; 
}

Segment Snake::GetHead()
{
  return Segment(_segments[0]);
};

std::vector<Segment>& Snake::GetSegments()
{
  return _segments;
}

void Snake::ClearSnakeTail(Adafruit_SPITFT* display)
{
  if (_removedSegments.size() > 0)
  {
    for (auto seg : _removedSegments)
    {
      seg.Clear(display);
    }
    _removedSegments.clear();
  }
}

void Snake::DrawSnake(Adafruit_SPITFT* display)
{
  for (auto& segment : _segments)
  {
    segment.Draw(display);
  }
}

// segments never change once drawn, so each frame only the new head needs drawing
void Snake::DrawSnakeUpdate(Adafruit_SPITFT* display)
{
  _segments[0].Draw(display);
}