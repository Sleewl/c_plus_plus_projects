#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include "Point.h"

#include "Shape.h"

#include "FrameRectangle.h"

#include <exception>

#include <string>



class Parallelogram : public Shape
{
public:

	Parallelogram(Point a, Point b, Point c) :
		a_(a),
		b_(b),
		c_(c)
	{
		if (((b_.getX() - a_.getX()) * (c_.getY() - a_.getY())) == ((b_.getY() - a_.getY()) * (c_.getX() - a_.getX()))) { // Проверка, если точки лежат на одной прямой -> точки не задают треугольник
			throw std::runtime_error("Ошибка, точки не задают треугольник ");
		}
		if (!((a_.getY() == b_.getY() && a_.getX() != b_.getX() && b_.getX() != c_.getX() && b_.getY() != c_.getY()) ||
			(a_.getY() != b_.getY() && a_.getX() != b_.getX() && b_.getX() == c_.getX() && b_.getY() != c_.getY()))) { //Проверка, на параллельность параллелограмма осям
			throw std::runtime_error("Ошибка, стороны параллелограмма не параллелен осям ");
		}
	}

	~Parallelogram(){}

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
	void move(double dX, double dY) override;
	void scale(double coef) override;
	Shape* clone() const override;
	std::string getName() const override;
	void getInfo(std::ostream& out) const override;


private:
	Point a_;
	Point b_;
	Point c_;

};


#endif

