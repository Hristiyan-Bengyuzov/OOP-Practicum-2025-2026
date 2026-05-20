#include "LowerCaseStrategy.h"
#include <algorithm>

std::string LowerCaseStrategy::apply(const std::string& input) const
{
	std::string res = input;
	std::transform(res.begin(), res.end(), res.begin(), ::tolower);
	return res;
}

std::string LowerCaseStrategy::name() const
{
	return "LowerCase";
}
