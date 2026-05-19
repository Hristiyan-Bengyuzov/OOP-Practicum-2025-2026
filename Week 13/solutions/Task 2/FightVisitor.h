#pragma once
#include "Outcome.h"
#include "Gestures.h"

struct FightVisitor {
	// Rock
	Outcome operator()(const Rock& a, const Rock& b) const;
	Outcome operator()(const Rock& a, const Paper& b) const;
	Outcome operator()(const Rock& a, const Scissors& b) const;
	Outcome operator()(const Rock& a, const Lizard& b) const;
	Outcome operator()(const Rock& a, const Spock& b) const;

	// Paper
	Outcome operator()(const Paper& a, const Rock& b) const;
	Outcome operator()(const Paper& a, const Paper& b) const;
	Outcome operator()(const Paper& a, const Scissors& b) const;
	Outcome operator()(const Paper& a, const Lizard& b) const;
	Outcome operator()(const Paper& a, const Spock& b) const;

	// Scissors
	Outcome operator()(const Scissors& a, const Rock& b) const;
	Outcome operator()(const Scissors& a, const Paper& b) const;
	Outcome operator()(const Scissors& a, const Scissors& b) const;
	Outcome operator()(const Scissors& a, const Lizard& b) const;
	Outcome operator()(const Scissors& a, const Spock& b) const;

	// Lizard
	Outcome operator()(const Lizard& a, const Rock& b) const;
	Outcome operator()(const Lizard& a, const Paper& b) const;
	Outcome operator()(const Lizard& a, const Scissors& b) const;
	Outcome operator()(const Lizard& a, const Lizard& b) const;
	Outcome operator()(const Lizard& a, const Spock& b) const;

	// Spock
	Outcome operator()(const Spock& a, const Rock& b) const;
	Outcome operator()(const Spock& a, const Paper& b) const;
	Outcome operator()(const Spock& a, const Scissors& b) const;
	Outcome operator()(const Spock& a, const Lizard& b) const;
	Outcome operator()(const Spock& a, const Spock& b) const;
};

Outcome fight(const Gesture& a, const Gesture& b);