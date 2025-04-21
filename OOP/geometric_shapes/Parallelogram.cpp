#include "Parallelogram.h"

#include <cmath>

double Parallelogram::getArea() const {
	double Area = ((a_.getY() - c_.getY()) * (a_.getX() - b_.getX()));
	return Area;
}

FrameRectangle Parallelogram::getFrameRectangle() const {
	double width = b_.getX() - a_.getX() + b_.getX() - c_.getX();
	double height = a_.getY() - c_.getY();
	double centerX = (a_.getX() + c_.getX()) / 2;
	double centerY = (a_.getY() + c_.getY()) / 2;

	Point center(centerX, centerY);
	FrameRectangle newFrameRectangle(width, height, center);
    return newFrameRectangle;
}

void Parallelogram::move(double dX, double dY) {
	a_.move(dX, dY);
	b_.move(dX, dY);
}

void Parallelogram::scale(double coef) {
	double scaleAk = (a_.getX() + a_.getY()) * coef;
	double scaleBk = (b_.getX() + b_.getY()) * coef;
	double scaleCk = (c_.getX() + c_.getY()) * coef;

	double scaleA = (a_.getX() + a_.getY());
	double scaleB = (b_.getX() + b_.getY());
	double scaleC = (c_.getX() + c_.getY());

	a_.move( (-(scaleAk - scaleA)) / 2, (scaleBk - scaleB) / 2);
	b_.move( (scaleAk - scaleA) / 2, (scaleBk - scaleB) / 2);
	c_.move((scaleAk - scaleA) / 2, (-(scaleBk - scaleB)) / 2);
}

Shape* Parallelogram::clone() const {
	return new Parallelogram(*this);
}

std::string Parallelogram::getName() const {
	return "Parallelogram";
}


void Parallelogram::getInfo(std::ostream& out) const {
	out << "Parallelogram Info:" << std::endl;
	out << "Vertices: " << getA() << ", " << getB() << ", " << getC() << std::endl;
}
