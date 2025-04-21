#include "Triangle.h"

#include <iostream>

using namespace std;

Triangle::Triangle() : a_(Point()), b_(Point()), c_(Point()) {}

Triangle::Triangle(const Point& a, const Point& b, const Point& c) : a_(a), b_(b), c_(c) {}

Point Triangle::getA() const {
    return a_;
}

Point Triangle::getB() const {
    return b_;
}

Point Triangle::getC() const {
    return c_;
}

void Triangle::setA(const Point& a) {
    a_ = a;
}

void Triangle::setB(const Point& b) {
    b_ = b;
}

void Triangle::setC(const Point& c) {
    c_ = c;
}

double Triangle::getPerimeter() const {
    double side1 = std::sqrt(std::pow(b_.getX() - a_.getX(), 2) + std::pow(b_.getY() - a_.getY(), 2));
    double side2 = std::sqrt(std::pow(c_.getX() - b_.getX(), 2) + std::pow(c_.getY() - b_.getY(), 2));
    double side3 = std::sqrt(std::pow(a_.getX() - c_.getX(), 2) + std::pow(a_.getY() - c_.getY(), 2));

    return side1 + side2 + side3;
}

bool Triangle::operator==(const Triangle& other) const {
    return a_ == other.a_ && b_ == other.b_ && c_ == other.c_;
}

double calculateArea(const Point& p1, const Point& p2, const Point& p3) {
    return 0.5 * std::abs(p1.getX() * (p2.getY() - p3.getY()) +
        p2.getX() * (p3.getY() - p1.getY()) +
        p3.getX() * (p1.getY() - p2.getY()));
}

bool Triangle::operator<(const Triangle& other) const {
    double area1 = calculateArea(a_, b_, c_);
    double area2 = calculateArea(other.a_, other.b_, other.c_);

    return area1 < area2;
}

Triangle Triangle::operator+(double k) const {
    return Triangle(a_ + k, b_ + k, c_ + k);
}

Triangle& Triangle::operator+=(double k) {
    a_ += k;
    b_ += k;
    c_ += k;
    return *this;
}

ostream& operator<<(ostream& out, const Triangle& triangle) {
    out << "Triangle: A" << triangle.a_ << ", B" << triangle.b_ << ", C" << triangle.c_;
    return out;
}

istream& operator>>(istream& in, Triangle& triangle) {
    in >> triangle.a_ >> triangle.b_ >> triangle.c_;
    return in;
}
