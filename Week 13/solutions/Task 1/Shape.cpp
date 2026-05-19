#include "Shape.h"

void Shape::print(std::ostream& os) const
{
	std::println(
		os,
		"{}: area={:.2f}, perimeter={:.2f}",
		getName(),
		getArea(),
		getPerimeter()
	);
}

Shape::~Shape() = default;
