#pragma once
#include "ValidationUtils.hpp"
#include <numbers>
#include <iostream>

class Shape {
public:
	virtual double getArea() const = 0;
	virtual double getPerimeter() const = 0;
	virtual std::string getName() const = 0;
	virtual void print(std::ostream& os) const;
	virtual ~Shape();
};