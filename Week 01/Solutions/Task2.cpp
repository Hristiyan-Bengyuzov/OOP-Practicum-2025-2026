#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Triangle {
	double a, b, c;

	// Heronova formula
	double getArea() const {
		double p = (a + b + c) / 2.0;
		return std::sqrt(p * (p - a) * (p - b) * (p - c));
	}

	void print(std::ostream& os = std::cout) const {
		os << "a=" << a
			<< " b=" << b
			<< " c=" << c
			<< " Area=" << getArea()
			<< std::endl;
	}
};

int main() {
	size_t n;
	std::cin >> n;

	std::vector<Triangle> triangles(n);

	for (size_t i = 0; i < n; i++) {
		std::cin >> triangles[i].a >> triangles[i].b >> triangles[i].c;
	}

	// you can use any sorting algorithm but we usually sort vectors with this function
	// we always pass the beginning and end of our vector
	// the third optional parameter is a lambda where we tell it how we sort it
	// if we use < for comparison, that means we want it sorted in ascending order. if we use > it means descending order
	// if we don't pass anything it uses the < operator of the struct
	std::sort(triangles.begin(), triangles.end(), [](const Triangle& t1, const Triangle& t2) {
		return t1.getArea() < t2.getArea();
		});

	for (const Triangle& t : triangles) {
		t.print();
	}
}