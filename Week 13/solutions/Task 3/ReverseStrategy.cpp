#include "ReverseStrategy.h"
#include <algorithm>

std::string ReverseStrategy::apply(const std::string& input) const
{
	std::string res = input;
	std::reverse(res.begin(), res.end());
	return res;
}

std::string ReverseStrategy::name() const
{
	return "Reverse";
}
