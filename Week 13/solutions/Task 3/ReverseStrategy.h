#pragma once
#include "TextStrategy.h"

class ReverseStrategy : public TextStrategy {
public:
	std::string apply(const std::string& input) const override;
	std::string name() const override;
};
