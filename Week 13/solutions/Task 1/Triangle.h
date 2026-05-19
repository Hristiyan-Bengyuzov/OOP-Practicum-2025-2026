#pragma once
#include "Shape.h"

class Triangle : public Shape {
private:
	double a_;
	double b_;
	double c_;

public:
	Triangle(double a, double b, double c);

	double getArea() const override;
	double getPerimeter() const override;
	std::string getName() const override;
};