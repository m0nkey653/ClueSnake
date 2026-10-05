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
    if (!IsVertical())
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
    // origin of the next segment, based on the current heading and the new one
    Point origin;
    switch (_direction)
    {
        case Direction::East:
            switch (direction)
            {
                case Direction::East:  origin = { _topLeft._x + _height, _topLeft._y }; break;
                case Direction::South: origin = { _bottomRight._x - _width, _bottomRight._y }; break;
                case Direction::North: origin = { _topRight._x - _width, _topRight._y - _height }; break;
                default: return Segment(*this);
            }
            break;

        case Direction::West:
            switch (direction)
            {
                case Direction::West:  origin = { _topLeft._x - _height, _topLeft._y }; break;
                case Direction::South: origin = _bottomLeft; break;
                case Direction::North: origin = { _topLeft._x, _topLeft._y - _height }; break;
                default: return Segment(*this);
            }
            break;

        case Direction::North:
            switch (direction)
            {
                case Direction::North: origin = { _topLeft._x, _topLeft._y - _height }; break;
                case Direction::East:  origin = _topRight; break;
                case Direction::West:  origin = { _topLeft._x - _height, _topLeft._y }; break;
                default: return Segment(*this);
            }
            break;

        case Direction::South:
            switch (direction)
            {
                case Direction::South: origin = { _topLeft._x, _topLeft._y + _height }; break;
                case Direction::East:  origin = { _bottomRight._x, _bottomRight._y - _width }; break;
                case Direction::West:  origin = { _bottomLeft._x - _height, _bottomLeft._y - _width }; break;
                default: return Segment(*this);
            }
            break;

        default:
            return Segment(*this);
    }

    return Segment(origin, _color, direction, _width, _height);
}

void Segment::Draw(Adafruit_SPITFT* tft)
{
    Fill(tft, _color);
}

void Segment::Clear(Adafruit_SPITFT* tft)
{
    Fill(tft, ARCADA_BLACK);
}

bool Segment::IsVertical()
{
    return _direction == Direction::North || _direction == Direction::South;
}

void Segment::Fill(Adafruit_SPITFT* tft, int color)
{
    // width and height are defined for a vertical segment, so swap them when horizontal
    if (IsVertical())
    {
        tft->fillRect(_topLeft._x, _topLeft._y, _width, _height, color);
    }
    else
    {
        tft->fillRect(_topLeft._x, _topLeft._y, _height, _width, color);
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