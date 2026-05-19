#pragma once
#include "Outcome.h"
#include "Gestures.h"
#include <iostream>

struct NameVisitor {
	std::string operator()(const Rock& rock) const;
	std::string operator()(const Paper& paper) const;
	std::string operator()(const Scissors& scissors) const;
	std::string operator()(const Lizard& lizard) const;
	std::string operator()(const Spock& spock) const;
};

std::string getGestureName(const Gesture& gesture);