#ifndef SNAKE_SEGMENT
#define SNAKE_SEGMENT

#include <vector>
#include <Adafruit_SPITFT.h>
#include "Point.h"
#include "Common.h"

class Segment
{
public:

    Segment() = default;
    Segment(Point topLeft, int color, Direction direction, int width, int height);
    void Draw(Adafruit_SPITFT* display);
    void Clear(Adafruit_SPITFT* display);
    
    bool Intersects(Segment& segment);
    bool Intersects(Point& point);
    
    Segment GetNext(Direction direction);

    Segment& operator=(const Segment& segment);

    Point _topLeft = {};
    Point _topRight = {};
    Point _bottomRight = {};
    Point _bottomLeft = {};

    int _color = 0;
    int _width = 0;
    int _height = 0;
    Direction _direction = Direction::Unset;
private:
};

#endif