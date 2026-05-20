#include "TextProcessor.h"
#include <algorithm>

TextProcessor& TextProcessor::addStrategy(std::unique_ptr<TextStrategy> strategy)
{
	pipeline_.push_back(std::move(strategy));
	return *this;
}

TextProcessor& TextProcessor::removeStrategy(const std::string& name)
{
	std::erase_if(pipeline_, [&name](const std::unique_ptr<TextStrategy>& strategy) {
		return strategy->name() == name;
	});

	return *this;
}

std::string TextProcessor::process(const std::string& input) const
{
	std::string res = input;

	for (const auto& strategy : pipeline_) {
		res = strategy->apply(res);
	}

	return res;
}

void TextProcessor::printPipeline(std::ostream& os) const
{
	std::print(os, "Pipeline: ");

	for (size_t i = 0; i < pipeline_.size(); i++)
	{
		if (i > 0)
		{
			std::print(os, " -> ");
		}

		std::print(os, "[{}]", pipeline_[i]->name());
	}

	std::println(os);
}

void TextProcessor::clearPipeline()
{
	pipeline_.clear();
}
