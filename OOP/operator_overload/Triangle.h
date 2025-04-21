#include "Point.h"

#include <iostream>

using namespace std;



class Triangle {
private:
    Point a_;
    Point b_;
    Point c_;

public:
    Triangle();
    Triangle(const Point& a, const Point& b, const Point& c);

    Point getA() const;
    Point getB() const;
    Point getC() const;


    void setA(const Point& a);
    void setB(const Point& b);
    void setC(const Point& c);

    double getPerimeter() const;

    bool operator==(const Triangle& other) const;
    bool operator<(const Triangle& other) const;
    Triangle operator+(double k) const;
    Triangle& operator+=(double k);

    friend ostream& operator<<(ostream& out, const Triangle& triangle);
    friend istream& operator>>(istream& in, Triangle& triangle);
};

