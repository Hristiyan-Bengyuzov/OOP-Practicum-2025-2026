#include "ReplaceUtil.h"

void replaceAll(std::string& text, const std::string& from, const std::string& to)
{
	if (from.empty())
		return;

	size_t pos = 0;

	while ((pos = text.find(from, pos)) != std::string::npos)
	{
		text.replace(pos, from.length(), to);
		pos += to.length();
	}
}
