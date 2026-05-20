#pragma once
#include "TextStrategy.h"

class LowerCaseStrategy : public TextStrategy {
	std::string apply(const std::string& input) const override;
	std::string name() const override;
};
