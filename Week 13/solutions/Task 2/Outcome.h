#pragma once
#include <string>

enum class Outcome {
	Win,
	Loss,
	Draw
};

std::string toString(Outcome o);