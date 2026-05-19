#pragma once
#include <vector>
#include "NameVisitor.h"
#include "FightVisitor.h"

class Game {
private:
	std::vector<std::pair<Gesture, Gesture>> history_;
	int winsA_, winsB_, draws_;

public:
	Outcome playRound(const Gesture& a, const Gesture& b);
	void printScore(std::ostream& os) const;
	void printHistory(std::ostream& os) const;
};