#include "Point.h"

#include <iostream>

using namespace std;

#include <cmath>

Point::Point() : x_(0.0), y_(0.0) {}

Point::Point(double x, double y) : x_(x), y_(y) {}

void Point::setX(double x) {
    x_ = x;
}

void Point::setY(double y) {
    y_ = y;
}

double Point::getX() const {
    return x_;
}

double Point::getY() const {
    return y_;
}

bool Point::operator==(const Point& other) const {
    return x_ == other.x_ && y_ == other.y_;
}

bool Point::operator<(const Point& other) const {
    return (x_ * x_ + y_ * y_) < (other.x_ * other.x_ + other.y_ * other.y_);
}

Point Point::operator+(double k) const {
    return Point(x_ + k, y_ + k);
}

Point& Point::operator+=(double k) {
    x_ += k;
    y_ += k;
    return *this;
}

ostream& operator<<(ostream& out, const Point& point) {
    out << "(" << point.x_ << ", " << point.y_ << ")";
    return out;
}

istream& operator>>(istream& in, Point& point) {
    in >> point.x_ >> point.y_;
    return in;
}
