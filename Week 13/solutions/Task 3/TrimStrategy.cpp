#include "TrimStrategy.h"

std::string TrimStrategy::apply(const std::string& input) const
{
	size_t start = 0;
	size_t end = input.length() - 1;

	while (start <= end && std::isspace(input[start]))
		start++;

	while (end >= start && std::isspace(input[end]))
		end--;

	return input.substr(start, end - start + 1);
}

std::string TrimStrategy::name() const
{
	return "Trim";
}
