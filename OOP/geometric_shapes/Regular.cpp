#include "Regular.h"

double Regular::getArea() const {
	double Area = (c_.getX() - b_.getX()) * (c_.getX() - b_.getX()) * 4;
	return Area;
}

FrameRectangle Regular::getFrameRectangle() const {
	double width = (c_.getX() - b_.getX()) * 2;
	double height = (b_.getY() - a_.getY()) * 2;
	double centerX = a_.getX();
	double centerY = a_.getY();

	Point center(centerX, centerY);
	FrameRectangle newFrameRectangle(width, height, center);
	return newFrameRectangle;
}

void Regular::move(double dX, double dY) {
	a_.move(dX, dY);
	b_.move(dX, dY);
	c_.move(dX, dY);
}

void Regular::scale(double coef) {
	b_.move(0, (b_.getY() - a_.getY()) * coef - (b_.getY() - a_.getY()));
	c_.move((c_.getX() - a_.getX()) * coef - (c_.getX() - a_.getX()), (c_.getY() - a_.getY()) * coef - (c_.getY() - a_.getY()));
}


Shape* Regular::clone() const {
	return new Regular(*this);
}

std::string Regular::getName() const {
	return "Regular";
}


void Regular::getInfo(std::ostream& out) const {
	out << "Regular Info:" << std::endl;
	out << "Vertices: " << getA() << ", " << getB() << ", " << getC() << std::endl;
}
