#pragma once
#include <iostream>
#include <vector>
#include "TextStrategy.h"

class CensorStrategy : public TextStrategy {
private:
	std::vector<std::string> bannedWords_;

public:
	CensorStrategy(std::vector<std::string> bannedWords);

	std::string apply(const std::string& input) const override;
	std::string name() const override;
};