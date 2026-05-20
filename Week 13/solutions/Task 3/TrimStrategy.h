#pragma once
#include "TextStrategy.h"

class TrimStrategy : public TextStrategy {
	std::string apply(const std::string& input) const override;
	std::string name() const override;
};
