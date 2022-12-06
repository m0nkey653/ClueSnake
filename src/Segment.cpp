#include "Segment.h"
#include "Colors.h"

Segment& Segment::operator=(const Segment& segment)
{
    _topLeft = segment._topLeft;
    _topRight = segment._topRight;
    _bottomRight = segment._bottomRight;
    _bottomLeft = segment._bottomLeft;
    _color = segment._color;
    _width = segment._width;
    _height = segment._height;
    _direction = segment._direction;
    
    return *this;
}

Segment::Segment(Point topLeft, int color, Direction direction, int width, int height)
    : _topLeft(topLeft),
    _color(color),
    _width(width),
    _height(height),
    _direction(direction)
{
    int tempWidth = width;
    int tempHeight = height;
    if (direction == Direction::East || direction == Direction::West)
    {
        tempWidth = height;
        tempHeight = width;
    }

    _topRight = {(topLeft._x + tempWidth), topLeft._y };
    _bottomRight = { topLeft._x + tempWidth, topLeft._y + tempHeight };
    _bottomLeft = { topLeft._x, topLeft._y + tempHeight };
}

Segment Segment::GetNext(Direction direction)
{
    if (_direction == Direction::East)
    {
        if (direction == Direction::East)
        {
            Point origin = { _topLeft._x + _height, _topLeft._y };
            return Segment(origin, _color, direction, _width, _height);
        }
        if (direction == Direction::South)
        {
            Point origin = { _bottomRight._x - _width, _bottomRight._y };
            return Segment(origin, _color, direction, _width, _height);
        }
        if (direction == Direction::North)
        {
            Point origin = { _topRight._x - _width, _topRight._y - _height };
            return Segment(origin, _color, direction, _width, _height);
        }
    }
    if (_direction == Direction::West)
    {
        if (direction == Direction::West)
        {
            Point origin = { _topLeft._x - _height, _topLeft._y };
            return Segment(origin, _color, direction, _width, _height);
        }
        if (direction == Direction::South)
        {
            Point origin = _bottomLeft;
            return Segment(origin, _color, direction, _width, _height);
        }
        if (direction == Direction::North)
        {
            Point origin = { _topLeft._x, _topLeft._y - _height };
            return Segment(origin, _color, direction, _width, _height);
        }
    }
    
    if (_direction == Direction::North)
    {
        if (direction == Direction::North)
        {
            Point origin = { _topLeft._x, _topLeft._y - _height };
            return Segment(origin, _color, direction, _width, _height);
        }
        if (direction == Direction::East)
        {
            Point origin = _topRight;
            return Segment(origin, _color, direction, _width, _height);
        }
        if (direction == Direction::West)
        {
            Point origin = { _topLeft._x - _height, _topLeft._y };
            return Segment(origin, _color, direction, _width, _height);
        }
    }
    if (_direction == Direction::South)
    {
        if (direction == Direction::South)
        {
            Point origin = { _topLeft._x, _topLeft._y + _height };
            return Segment(origin, _color, direction, _width, _height);
        }
        if (direction == Direction::East)
        {
            Point origin = { _bottomRight._x, _bottomRight._y - _width };
            return Segment(origin, _color, direction, _width, _height);
        }
        if (direction == Direction::West)
        {
            Point origin = { _bottomLeft._x - _height, _bottomLeft._y - _width };
            return Segment(origin, _color, direction, _width, _height);
        }
    }

    return Segment(*this);
}

void Segment::Draw(Adafruit_SPITFT* tft)
{
    if (_direction == Direction::North || _direction == Direction::South)
    {
        tft->fillRect(_topLeft._x, _topLeft._y, _width, _height, _color);
    }
    else
    {
        tft->fillRect(_topLeft._x, _topLeft._y, _height, _width, _color);
    }
}

void Segment::Clear(Adafruit_SPITFT* tft)
{
    if (_direction == Direction::North || _direction == Direction::South)
    {
        tft->fillRect(_topLeft._x, _topLeft._y, _width, _height, ARCADA_BLACK);
    }
    else
    {
        tft->fillRect(_topLeft._x, _topLeft._y, _height, _width, ARCADA_BLACK);
    }
}

bool Segment::Intersects(Segment& segment)
{
    return
        Intersects(segment._topLeft)
        || Intersects(segment._topRight)
        || Intersects(segment._bottomRight)
        || Intersects(segment._bottomLeft);
}

bool Segment::Intersects(Point& point)
{
    return
        point._x >= _topLeft._x
        && point._x <= _topRight._x
        && point._y >= _topLeft._y
        && point._y <= _bottomLeft._y;
}