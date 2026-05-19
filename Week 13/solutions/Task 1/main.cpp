#include <iostream>
#include "ShapeCollection.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

int main()
{
	ShapeCollection col;
	col.add(std::make_unique<Circle>(5.0));
	col.add(std::make_unique<Rectangle>(4.0, 6.0));
	col.add(std::make_unique<Triangle>(3.0, 4.0, 5.0));

	col.printAll(std::cout);
	// Circle: area=78.54, perimeter=31.42
	// Rectangle: area=24.00, perimeter=20.00
	// Triangle: area=6.00, perimeter=12.00

	std::cout << col.getLargestByArea()->getName() << std::endl; // Circle
	std::cout << col.getTotalArea(); // 108.54
}