#include "Point.h"

#include <iostream>

#include <cmath>

using namespace std;

string const WRONG_INPUT = "INCORRECT INPUT";


Point::Point(){
    x_ = 0.0;
    y_ = 0.0;
}

Point::Point(double x, double y){

    x_ = x;
    y_ = y;
}

Point::Point(const Point& other){

    x_ = other.x_;
    y_ = other.y_;

}

Point::~Point() {}

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

bool Point::isEqual(const Point& other) const {
    return x_ == other.x_ && y_ == other.y_;
}

double Point::getDistance(const Point& other) const {
    double deltaX = x_ - other.x_;
    double deltaY = y_ - other.y_;
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

void Point::move(double deltaX, double deltaY) {
    x_ += deltaX;
    y_ += deltaY;
}

bool isPointInCircle(const Point& point, double radius) {
    double distance = sqrt(point.getX() * point.getX() + point.getY() * point.getY());
    return distance <= radius;
}

void input(Point& point) {
    double x, y;
    cout << "Enter x and y coordinates separated by space: " << endl;
    try {
        cin >> x >> y;
        if (!cin) {
            throw(WRONG_INPUT);
        }
        point.setX(x);
        point.setY(y);

    }
    catch (const string thr) {
        cerr << "Error: " << thr <<  endl;
        exit(EXIT_FAILURE);

    }
    
}


void output(const Point& point) {
    cout << "(" << point.getX() << ", " << point.getY() << ")";
}
