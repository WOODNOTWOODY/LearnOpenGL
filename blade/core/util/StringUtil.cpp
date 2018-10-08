#include "CoreStd.h"
#include "StringUtil.h"

BLADE_NAMESPACE_BEGIN

const std::string StringUtil::BLANK;

std::vector<std::string> StringUtil::Split(const std::string& str, const std::string& delims = ", ", uint32 maxSplits = 0)
{
	std::vector<std::string> strs;
	strs.reserve(maxSplits ? maxSplits + 1 : 16);

	uint32 numSplits = 0;

	size_t start, pos;
	start = 0;
	do
	{
		pos = str.find_first_of(delims, start);
		if (pos == start)
		{
			start = pos + 1;
		}
		else if (pos == std::string::npos || (maxSplits && numSplits == maxSplits))
		{
			strs.push_back(str.substr(start));
			break;
		}
		else
		{
			strs.push_back(str.substr(start, pos - start));
			start = pos + 1;
		}

		start = str.find_first_not_of(delims, start);
		++numSplits;
	} while (pos != std::string::npos);

	return strs;
}

uint32 StringUtil::ParseUI32(const std::string& val, uint32 defVal)
{
	uint32 ret;
	if (sscanf(val.c_str(), "%u", &ret) != 1)
	{
		ret = defVal;
	}
	return ret;
}

BLADE_NAMESPACE_END