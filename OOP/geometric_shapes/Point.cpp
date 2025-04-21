#include "Point.h"

#include <cmath>

double Point::getDistance(const Point& p) const {
    return std::sqrt((x_ - p.x_) * (x_ - p.x_) + (y_ - p.y_) * (y_ - p.y_));
}
void Point::move(double xK, double yK) {
    x_ += xK;
    y_ += yK;
}

void Point::swap(Point& other) {
    std::swap(x_, other.x_);
    std::swap(y_, other.y_);
}

Point& Point::operator=(const Point& p) {
    x_ = p.x_;
    y_ = p.y_;
    return *this;
};

bool Point::operator==(const Point& p) const {
    return (p.x_ == x_ && p.y_ == y_);
};



bool Point::operator<(Point& p) const {
    return (x_ * x_ + y_ * y_ < p.x_ * p.x_ + p.y_ * p.y_);
};

bool Point::operator>=(Point& p) const {
    return (x_ * x_ + y_ * y_ >= p.x_ * p.x_ + p.y_ * p.y_);
};

Point Point::operator+(double k) {
    Point temp;
    temp.move(k, k);
    return temp;
};

Point& Point::operator+=(double k) {
    this->move(k, k);
    return *this;
};

std::ostream& operator<<(std::ostream& outputStream, const Point& p) {
    outputStream << "(" << p.x_ << ";" << p.y_ << ")";
    return outputStream;
};

std::istream& operator>>(std::istream& inputStream, Point& p) {
    inputStream >> p.x_ >> p.y_;
    return inputStream;
};
