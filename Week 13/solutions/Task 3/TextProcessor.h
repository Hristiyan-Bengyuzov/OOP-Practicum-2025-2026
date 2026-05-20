#pragma once
#include <vector>
#include <iostream>
#include "TextStrategy.h"

class TextProcessor {
private:
	std::vector<std::unique_ptr<TextStrategy>> pipeline_;

public:
	TextProcessor& addStrategy(std::unique_ptr<TextStrategy> strategy);
	TextProcessor& removeStrategy(const std::string& name);
	std::string process(const std::string& input) const;
	void printPipeline(std::ostream& os) const;
	void clearPipeline();
};