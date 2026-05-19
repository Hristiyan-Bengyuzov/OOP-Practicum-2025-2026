#pragma once
#include "Shape.h"

class Circle : public Shape {
private:
	double radius_;

public:
	Circle(double radius);

	double getArea() const override;
	double getPerimeter() const override;
	std::string getName() const override;
};