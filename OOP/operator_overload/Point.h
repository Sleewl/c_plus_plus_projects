#pragma once

#include <iostream>

using namespace std;


class Point {
private:
    double x_;
    double y_;

public:
    Point();
    Point(double x, double y);

    void setX(double x);
    void setY(double y);
    double getX() const;
    double getY() const;

    bool operator==(const Point& other) const;
    bool operator<(const Point& other) const;
    Point operator+(double k) const;
    Point& operator+=(double k);

    friend ostream& operator<<(ostream& out, const Point& point);
    friend istream& operator>>(istream& in, Point& point);
};
