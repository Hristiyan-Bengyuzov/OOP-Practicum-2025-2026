#include "ShapeCollection.h"

void ShapeCollection::add(std::unique_ptr<Shape> shape)
{
	shapes_.push_back(std::move(shape));
}

double ShapeCollection::getTotalArea() const
{
	double area = 0;

	for (const auto& shape : shapes_) {
		area += shape->getArea();
	}

	return area;
}

double ShapeCollection::getTotalPerimeter() const
{
	double perimeter = 0;

	for (const auto& shape : shapes_) {
		perimeter += shape->getPerimeter();
	}

	return perimeter;
}

const Shape* ShapeCollection::getLargestByArea() const
{
	if (shapes_.empty())
		return nullptr;

	return std::max_element(shapes_.begin(), shapes_.end(), [](const auto& a, const auto& b) {
		return a->getArea() < b->getArea();
	})->get();
}

const Shape* ShapeCollection::getSmallestByArea() const
{
	if (shapes_.empty())
		return nullptr;

	return std::min_element(shapes_.begin(), shapes_.end(), [](const auto& a, const auto& b) {
		return a->getArea() < b->getArea();
	})->get();
}

void ShapeCollection::printAll(std::ostream& os) const
{
	for (const auto& shape : shapes_) {
		shape->print(os);
	}
}

std::vector<const Shape*> ShapeCollection::filterByMinArea(double minArea) const
{
	std::vector<const Shape*> res;

	for (const auto& shape : shapes_) {
		if (shape->getArea() >= minArea)
		{
			res.push_back(shape.get());
		}
	}

	return res;
}
