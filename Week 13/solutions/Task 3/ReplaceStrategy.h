#pragma once
#include "TextStrategy.h"

class ReplaceStrategy : public TextStrategy {
private:
	std::string from_;
	std::string to_;

public:
	ReplaceStrategy(std::string from, std::string to);

	std::string apply(const std::string& input) const override;
	std::string name() const override;
};
