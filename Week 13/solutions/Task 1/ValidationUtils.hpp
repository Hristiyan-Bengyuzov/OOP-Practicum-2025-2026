#pragma once
#include <concepts>
#include <iostream>

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

class ValidationUtils {
public:
	template <Number T>
	static T validatePositive(T value, const std::string& field) {
		if (value <= 0)
		{
			throw std::invalid_argument(field + " must be positive");
		}

		return value;
	}

	template <Number T>
	static void validateTriangleSides(T a, T b, T c) {
		if (a + b <= c || a + c <= b || b + c <= a)
		{
			throw std::invalid_argument("Invalid triangle sides");
		}
	}
};