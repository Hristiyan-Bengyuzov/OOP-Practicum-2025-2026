#include <iostream>
#include <cmath>

enum class Quadrant {
	AXIS = 0,
	FIRST,
	SECOND,
	THIRD,
	FOURTH
};

struct Point {
	double x;
	double y;

	void read(std::istream& is = std::cin) {
		is >> x >> y;
	}

	void print(std::ostream& os = std::cout) const {
		os << "(" << x << ", " << y << ")" << std::endl;
	}

	double distanceFromOrigin() const {
		return std::sqrt(x * x + y * y);
	}

	double distanceTo(const Point& other) const {
		double dx = x - other.x;
		double dy = y - other.y;
		return std::sqrt(dx * dx + dy * dy);
	}

	Quadrant quadrant() const {
		if (x > 0 && y > 0)
			return Quadrant::FIRST;

		if (x < 0 && y > 0)
			return Quadrant::SECOND;

		if (x < 0 && y < 0)
			return Quadrant::THIRD;

		if (x > 0 && y < 0)
			return Quadrant::FOURTH;

		return Quadrant::AXIS;
	}

	// x^2 + y^2 <= r^2
	// ako e < znachi e vutre
	// ako e = znachi e po kontura
	bool isInsideCircleOrOutline(double r) const {
		return distanceFromOrigin() <= r;
	}
};

int main() {
	Point p1, p2;

	std::cout << "Enter coordinates of point 1 (x y): ";
	p1.read();

	std::cout << "Enter coordinates of point 2 (x y): ";
	p2.read();

	std::cout << "Point 1: ";
	p1.print();

	std::cout << "Point 2: ";
	p2.print();

	std::cout << "Distance of Point 1 from origin: " << p1.distanceFromOrigin() << std::endl;

	std::cout << "Distance between points: " << p1.distanceTo(p2) << std::endl;

	int quad = (int)p1.quadrant();
	if (quad == 0)
		std::cout << "Point 1 lies on an axis." << std::endl;
	else
		std::cout << "Point 1 is in quadrant: " << quad << std::endl;

	double radius;
	std::cout << "Enter circle radius: ";
	std::cin >> radius;

	if (p1.isInsideCircleOrOutline(radius))
		std::cout << "Point 1 is inside or on the circle." << std::endl;
	else
		std::cout << "Point 1 is outside the circle." << std::endl;
}