#include "CensorStrategy.h"
#include "ReplaceUtil.h"

CensorStrategy::CensorStrategy(std::vector<std::string> bannedWords)
	: bannedWords_(std::move(bannedWords))
{
}

std::string CensorStrategy::apply(const std::string& input) const
{
	std::string res = input;

	for (const auto& bannedWord : bannedWords_) {
		std::string replacement(bannedWord.length(), '*');
		replaceAll(res, bannedWord, replacement);
	}

	return res;
}

std::string CensorStrategy::name() const
{
	return "Censor";
}
