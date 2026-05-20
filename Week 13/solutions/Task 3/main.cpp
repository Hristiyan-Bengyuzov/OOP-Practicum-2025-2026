#include <iostream>
#include "TextProcessor.h"
#include "CensorStrategy.h"
#include "UpperCaseStrategy.h"
#include "TrimStrategy.h"
#include "ReverseStrategy.h"
#include "LowerCaseStrategy.h"
#include "ReplaceStrategy.h"

int main()
{
	TextProcessor processor;

	processor
		.addStrategy(std::make_unique<TrimStrategy>())
		.addStrategy(std::make_unique<UpperCaseStrategy>())
		.addStrategy(std::make_unique<CensorStrategy>(std::vector<std::string>{"BAD", "UGLY"}));
	processor.printPipeline(std::cout);

	std::string input = "   Hello BAD World UGLY!   ";
	processor.removeStrategy("UpperCase");
	processor.addStrategy(std::make_unique<ReverseStrategy>());
	processor.printPipeline(std::cout);
	std::cout << processor.process(input) << std::endl;

	processor.clearPipeline();

	processor
		.addStrategy(std::make_unique<LowerCaseStrategy>())
		.addStrategy(std::make_unique<ReplaceStrategy>("world", "universe"));
	processor.printPipeline(std::cout);
	std::cout << processor.process("Hello World World");
}