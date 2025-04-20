

#include "Point.h"

class Triangle {
private:
    Point a_;
    Point b_;
    Point c_;

public:
    Triangle();
    Triangle(const Point& a, const Point& b, const Point& c);
    Triangle(const Triangle& other);
    ~Triangle();

    void setA(const Point& a);
    void setB(const Point& b);
    void setC(const Point& c);
    Point getA() const;
    Point getB() const;
    Point getC() const;

    bool isTriangle() const;
    void move(double deltaX, double deltaY);
    double getPerimeter() const;
    bool isEqual(const Triangle& other) const;
};

bool isEqualSquare(const Triangle& t1, const Triangle& t2);
void output(const Triangle& triangle);