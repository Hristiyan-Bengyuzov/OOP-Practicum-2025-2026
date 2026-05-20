#include "UpperCaseStrategy.h"
#include <algorithm>

std::string UpperCaseStrategy::apply(const std::string& input) const
{
	std::string res = input;
	std::transform(res.begin(), res.end(), res.begin(), ::toupper);
	return res;
}

std::string UpperCaseStrategy::name() const
{
	return "UpperCase";
}
