#include "Circle.h"

Circle::Circle(double radius)
	: radius_(ValidationUtils::validatePositive(radius, "Radius"))
{
}

double Circle::getArea() const
{
	return std::numbers::pi * radius_ * radius_;
}

double Circle::getPerimeter() const
{
	return 2 * std::numbers::pi * radius_;
}

std::string Circle::getName() const
{
	return "Circle";
}
