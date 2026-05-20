#include "ReplaceStrategy.h"
#include "ReplaceUtil.h"

ReplaceStrategy::ReplaceStrategy(std::string from, std::string to)
	: from_(std::move(from)), to_(std::move(to))
{
}

std::string ReplaceStrategy::apply(const std::string& input) const
{
	std::string res = input;
	replaceAll(res, from_, to_);
	return res;
}

std::string ReplaceStrategy::name() const
{
	return std::format("Replace({} -> {})", from_, to_);
}
