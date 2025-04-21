#include "Treagle.h"

#include <cmath>
#include <iostream>

Triangle::Triangle() : a_(Point()), b_(Point()), c_(Point()) {}

Triangle::Triangle(const Point& a, const Point& b, const Point& c) : a_(a), b_(b), c_(c) {}

Triangle::Triangle(const Triangle& other) : a_(other.a_), b_(other.b_), c_(other.c_) {}

Triangle::~Triangle() {}

void Triangle::setA(const Point& a) {
    a_ = a;
}

void Triangle::setB(const Point& b) {
    b_ = b;
}

void Triangle::setC(const Point& c) {
    c_ = c;
}

Point Triangle::getA() const {
    return a_;
}

Point Triangle::getB() const {
    return b_;
}

Point Triangle::getC() const {
    return c_;
}

bool Triangle::isTriangle() const {
    return !(a_.isEqual(b_) || b_.isEqual(c_) || c_.isEqual(a_));
}

void Triangle::move(double deltaX, double deltaY) {
    a_.move(deltaX, deltaY);
    b_.move(deltaX, deltaY);
    c_.move(deltaX, deltaY);
}

double Triangle::getPerimeter() const {
    double sideAB = a_.getDistance(b_);
    double sideBC = b_.getDistance(c_);
    double sideCA = c_.getDistance(a_);
    return sideAB + sideBC + sideCA;
}

bool Triangle::isEqual(const Triangle& other) const {
    return a_.isEqual(other.a_) && b_.isEqual(other.b_) && c_.isEqual(other.c_);
}

bool isEqualSquare(const Triangle& t1, const Triangle& t2) {
    return t1.isEqual(t2);
}

void output(const Triangle& triangle) {
    std::cout << "Triangle vertices: ";
    output(triangle.getA());
    std::cout << ", ";
    output(triangle.getB());
    std::cout << ", ";
    output(triangle.getC());
    std::cout << std::endl;
}