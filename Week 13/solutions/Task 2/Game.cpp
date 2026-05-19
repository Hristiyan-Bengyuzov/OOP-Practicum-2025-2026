#include "Game.h"

Outcome Game::playRound(const Gesture& a, const Gesture& b)
{
	Outcome outcome = fight(a, b);
	history_.emplace_back(a, b);

	switch (outcome)
	{
		case Outcome::Win:
			winsA_++;
			break;
		case Outcome::Loss:
			winsB_++;
			break;
		case Outcome::Draw:
			draws_++;
			break;
	}

	return outcome;
}

void Game::printScore(std::ostream& os) const
{
	std::println(os, "Player A: {} | Draws: {} | Player B: {}", winsA_, draws_, winsB_);
}

void Game::printHistory(std::ostream& os) const
{
	int round = 1;
	for (const auto& [a, b] : history_) {
		Outcome outcome = fight(a, b);

		std::println(
			os,
			"Round {}: {} vs {} -> {}",
			round++,
			getGestureName(a),
			getGestureName(b),
			toString(outcome)
		);
	}
}
