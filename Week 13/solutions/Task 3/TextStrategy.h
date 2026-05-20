#pragma once
#include <iostream>

class TextStrategy {
public:
	virtual std::string apply(const std::string& input) const = 0;
	virtual std::string name() const = 0;
	virtual ~TextStrategy() = default;
};
