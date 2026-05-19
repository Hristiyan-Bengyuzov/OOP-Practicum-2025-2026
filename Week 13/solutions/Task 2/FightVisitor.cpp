#include "FightVisitor.h"

Outcome FightVisitor::operator()(const Rock& a, const Rock& b) const
{
	return Outcome::Draw;
}

Outcome FightVisitor::operator()(const Rock& a, const Paper& b) const
{
	return Outcome::Loss;
}

Outcome FightVisitor::operator()(const Rock& a, const Scissors& b) const
{
	return Outcome::Win;
}

Outcome FightVisitor::operator()(const Rock& a, const Lizard& b) const
{
	return Outcome::Win;
}

Outcome FightVisitor::operator()(const Rock& a, const Spock& b) const
{
	return Outcome::Loss;
}

Outcome FightVisitor::operator()(const Paper& a, const Rock& b) const
{
	return Outcome::Win;
}

Outcome FightVisitor::operator()(const Paper& a, const Paper& b) const
{
	return Outcome::Draw;
}

Outcome FightVisitor::operator()(const Paper& a, const Scissors& b) const
{
	return Outcome::Loss;
}

Outcome FightVisitor::operator()(const Paper& a, const Lizard& b) const
{
	return Outcome::Loss;
}

Outcome FightVisitor::operator()(const Paper& a, const Spock& b) const
{
	return Outcome::Win;
}

Outcome FightVisitor::operator()(const Scissors& a, const Rock& b) const
{
	return Outcome::Loss;
}

Outcome FightVisitor::operator()(const Scissors& a, const Paper& b) const
{
	return Outcome::Win;
}

Outcome FightVisitor::operator()(const Scissors& a, const Scissors& b) const
{
	return Outcome::Draw;
}

Outcome FightVisitor::operator()(const Scissors& a, const Lizard& b) const
{
	return Outcome::Win;
}

Outcome FightVisitor::operator()(const Scissors& a, const Spock& b) const
{
	return Outcome::Loss;
}

Outcome FightVisitor::operator()(const Lizard& a, const Rock& b) const
{
	return Outcome::Loss;
}

Outcome FightVisitor::operator()(const Lizard& a, const Paper& b) const
{
	return Outcome::Win;
}

Outcome FightVisitor::operator()(const Lizard& a, const Scissors& b) const
{
	return Outcome::Loss;
}

Outcome FightVisitor::operator()(const Lizard& a, const Lizard& b) const
{
	return Outcome::Draw;
}

Outcome FightVisitor::operator()(const Lizard& a, const Spock& b) const
{
	return Outcome::Win;
}

Outcome FightVisitor::operator()(const Spock& a, const Rock& b) const
{
	return Outcome::Win;
}

Outcome FightVisitor::operator()(const Spock& a, const Paper& b) const
{
	return Outcome::Loss;
}

Outcome FightVisitor::operator()(const Spock& a, const Scissors& b) const
{
	return Outcome::Win;
}

Outcome FightVisitor::operator()(const Spock& a, const Lizard& b) const
{
	return Outcome::Loss;
}

Outcome FightVisitor::operator()(const Spock& a, const Spock& b) const
{
	return Outcome::Draw;
}

Outcome fight(const Gesture& a, const Gesture& b)
{
	return std::visit(FightVisitor{}, a, b);
}
