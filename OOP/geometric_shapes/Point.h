
#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
public:
    Point() :
        x_(0.0),
        y_(0.0)
    {}

    Point(double x, double y) :
        x_(x),
        y_(y)
    {}

    ~Point() {}

    void setX(double x) {
        x_ = x;
    }

    void setY(double y) {
        y_ = y;
    }

    double getX() const {
        return x_;
    }

    double getY() const {
        return y_;
    }

    double getDistance(const Point& p) const;
    void move(double xK, double yK);

    void swap(Point& other);

    bool operator==(const Point& p) const;
    bool operator<(Point& p) const;
    bool operator>=(Point& p) const;
    Point operator+(double k);
    Point& operator=(const Point& p);
    Point& operator+=(double k);

    friend std::ostream& operator<<(std::ostream& outputStream, const Point& p);
    friend std::istream& operator>>(std::istream& inputStream, Point& p);

private:
    double x_;
    double y_;
};

#endif



