#ifndef REGULAR_H
#define REGULAR_H

#include "Point.h"

#include "Shape.h"

#include "FrameRectangle.h"

#include <exception>

class Regular : public Shape
{
public:
	Regular(Point a, Point b, Point c) :
		a_(a),
		b_(b),
		c_(c)
	{
		if (pow(a_.getDistance(c_), 2) != pow(b_.getDistance(c_), 2) + pow(b_.getDistance(a_), 2)) {
			throw std::runtime_error("Ошибка, вершины не формируют прямоугольный треугольник ");
		}

	}

	~Regular(){}

	Point getA() const {
		return a_;
	}

	Point getB() const {
		return b_;
	}

	Point getC() const {
		return c_;
	}

	double getArea() const override;
	FrameRectangle getFrameRectangle() const override;
	void move(double x, double y) override;
	void scale(double factor) override;
	Shape* clone() const override;
	std::string getName() const override;
	
	void getInfo(std::ostream& out) const override;

	

private:
	Point a_;
	Point b_;
	Point c_;
};

#endif 

