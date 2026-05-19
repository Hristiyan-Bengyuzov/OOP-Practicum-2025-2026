#include "Outcome.h"

std::string toString(Outcome o)
{
	switch (o)
	{
		case Outcome::Win:
			return "Win";
			break;
		case Outcome::Loss:
			return "Loss";
			break;
		case Outcome::Draw:
			return "Draw";
			break;
		default:
			return "Invalid";
	}
}
