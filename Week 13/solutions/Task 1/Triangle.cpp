#include "Triangle.h"

Triangle::Triangle(double a, double b, double c)
	: a_(ValidationUtils::validatePositive(a, "Side a")),
	b_(ValidationUtils::validatePositive(b, "Side b")),
	c_(ValidationUtils::validatePositive(c, "Side c"))
{
	ValidationUtils::validateTriangleSides(a, b, c);
}

double Triangle::getArea() const
{
	double sp = getPerimeter() / 2;
	return std::sqrt(sp * (sp - a_) * (sp - b_) * (sp - c_));
}

double Triangle::getPerimeter() const
{
	return a_ + b_ + c_;
}

std::string Triangle::getName() const
{
	return "Triangle";
}
