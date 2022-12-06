#ifndef SNAKE_TREAT
#define SNAKE_TREAT

#include <Adafruit_SPITFT.h>
#include <vector>
#include "Point.h"
#include "Segment.h"

class Treat
{
public:
    Treat() = default;
    Treat(Point origin, int size, int color);
    bool SegmentIntersects(Segment segment);
    bool SegmentIntersects(std::vector<Segment> segments);
    void Draw(Adafruit_SPITFT* display);
    void Clear(Adafruit_SPITFT* display, Segment snakeHead);
private:
    Point _origin;
    int _size;
    int _color;
    std::vector<Point> _points;
};

#endif