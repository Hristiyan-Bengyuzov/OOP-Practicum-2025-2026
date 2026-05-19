#include "Rectangle.h"

Rectangle::Rectangle(double width, double height)
	: width_(ValidationUtils::validatePositive(width, "Width")),
	height_(ValidationUtils::validatePositive(height, "Height"))
{
}

double Rectangle::getArea() const
{
	return width_ * height_;
}

double Rectangle::getPerimeter() const
{
	return 2 * (width_ + height_);
}

std::string Rectangle::getName() const
{
	return "Rectangle";
}
