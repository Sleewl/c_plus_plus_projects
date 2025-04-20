#pragma once


class Point {
private:
    double x_;
    double y_;

public:
    Point();
    Point(double x, double y);
    Point(const Point& other);
    ~Point();

    void setX(double x);
    void setY(double y);
    double getX() const;
    double getY() const;
    bool isEqual(const Point& other) const;
    double getDistance(const Point& other) const;
    void move(double deltaX, double deltaY);
};

bool isPointInCircle(const Point& point, double radius);
void input(Point& point);
void output(const Point& point);


