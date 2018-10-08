#ifndef __BLADE_STRINGUTIL_H__
#define __BLADE_STRINGUTIL_H__

BLADE_NAMESPACE_BEGIN

class BLADE_CORE_API StringUtil
{
private:
	StringUtil() {}
	~StringUtil() {}

public:
	static const std::string BLANK;

public:
	static std::vector<std::string> Split(const std::string& str, const std::string& delims = ", ", uint32 maxSplits = 0);
	static uint32                   ParseUI32(const std::string& val, uint32 defVal = 0);
};

BLADE_NAMESPACE_END

#endif
