#include "NameVisitor.h"

std::string NameVisitor::operator()(const Rock& rock) const
{
	return "Rock";
}

std::string NameVisitor::operator()(const Paper& paper) const
{
	return "Paper";
}

std::string NameVisitor::operator()(const Scissors& scissors) const
{
	return "Scissors";
}

std::string NameVisitor::operator()(const Lizard& lizard) const
{
	return "Lizard";
}

std::string NameVisitor::operator()(const Spock& spock) const
{
	return "Spock";
}

std::string getGestureName(const Gesture& gesture)
{
	return std::visit(NameVisitor{}, gesture);
}
