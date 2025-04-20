#ifndef FRAMERECTANGLE_H
#define FRAMERECTANGLE_H
#include "Point.h"

class FrameRectangle
{
public:
    FrameRectangle() :
        width_(0.0),
        height_(0.0),
        center_(0.0, 0.0)
    {}

    FrameRectangle(double width, double height, Point center) :
        width_(width),
        height_(height),
        center_(center)
    {}

    ~FrameRectangle() {}

    double getWidth() const;
    double getHeight() const;
    Point getPos() const;
    
private:
    double width_;
    double height_;
    Point center_;
};

#endif //FRAMERECTANGLE_H
