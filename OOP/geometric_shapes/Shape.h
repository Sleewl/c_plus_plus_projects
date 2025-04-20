#ifndef SHAPE_H
#define SHAPE_H
#include "FrameRectangle.h"
#include <string>

class Shape
{
public:
    virtual double getArea() const = 0;
    virtual FrameRectangle getFrameRectangle() const = 0;
    virtual void move(double dX, double dY) = 0;
    virtual void scale(double coef) = 0;
    virtual Shape* clone() const = 0;
    virtual std::string getName() const = 0;
    //virtual void getInfo(std::ostream& out) const = 0;
    virtual void getInfo(std::ostream& out) const = 0;

};
#endif //SHAPE_H
