#include "Treat.h"
#include "Colors.h"

Treat::Treat(Point origin, int size, int color)
{
    _origin = origin;
    _size = size;
    _color = color;
    _points.push_back({origin._x, origin._y});
    _points.push_back({origin._x + size, origin._y});
    _points.push_back({origin._x, origin._y + size});
    _points.push_back({origin._x + size, origin._y + size});
}

bool Treat::SegmentIntersects(Segment snakeHead)
{
    for (auto p : _points)
    {
        if (snakeHead.Intersects(p))
        {
            return true;
        }
    }
    return false;
}

bool Treat::SegmentIntersects(std::vector<Segment> segments)
{
    for (auto p : _points)
    {
        for (auto segment : segments)
        {
            if (segment.Intersects(p))
            {
                return true;
            }
        }
    }
    return false;
}

void Treat::Draw(Adafruit_SPITFT* display)
{
    display->fillRoundRect(_points[0]._x, _points[0]._y, _size, _size, 5, _color);
}

void Treat::Clear(Adafruit_SPITFT* display, Segment snakeHead)
{
    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            Point p = { _origin._x + i, _origin._y + j };
            if (!snakeHead.Intersects(p))
            {
                display->drawPixel(p._x, p._y, ARCADA_BLACK);
            }
        }
    }
}