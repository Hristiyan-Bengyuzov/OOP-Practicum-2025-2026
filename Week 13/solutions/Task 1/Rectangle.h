#pragma once
#include "Shape.h"

class Rectangle : public Shape {
private:
	double width_;
	double height_;

public:
	Rectangle(double width, double height);

	double getArea() const override;
	double getPerimeter() const override;
	std::string getName() const override;
};