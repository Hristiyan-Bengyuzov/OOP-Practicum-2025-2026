#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct ComplexNumber {
	double real, imag;

	ComplexNumber add(const ComplexNumber& other) const {
		return { real + other.real, imag + other.imag };
	}

	ComplexNumber multiply(const ComplexNumber& other) const {
		return {
			real * other.real - imag * other.imag,
			real * other.imag + imag * other.real
		};
	}

	ComplexNumber divide(const ComplexNumber& other) const {
		double denominator = other.real * other.real + other.imag * other.imag;

		if (denominator == 0) {
			// should throw exception instead but not taken
			return {};
		}

		return {
			(real * other.real + imag * other.imag) / denominator,
			(imag * other.real - real * other.imag) / denominator
		};
	}

	// usually good practice to pass an ostream to print functions
	// that way you can reuse the code for something like writing in files, console, etc.
	void print(std::ostream& os = std::cout) const {
		os << real;

		if (imag >= 0)
			os << " + " << imag << "i" << std::endl;
		else
			os << " - " << -imag << "i" << std::endl;
	}
};

int main() {
	ComplexNumber c1, c2;

	std::cin >> c1.real >> c1.imag;
	std::cin >> c2.real >> c2.imag;

	std::cout << "First number: ";
	c1.print();

	std::cout << "Second number: ";
	c2.print();

	ComplexNumber sum = c1.add(c2);
	ComplexNumber product = c1.multiply(c2);
	ComplexNumber quotient = c1.divide(c2);

	std::cout << "Sum: ";
	sum.print();

	std::cout << "Product: ";
	product.print();

	std::cout << "Quotient: ";
	quotient.print();
}