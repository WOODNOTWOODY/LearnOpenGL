#ifndef __BLADE_PATHUTIL_H__
#define __BLADE_PATHUTIL_H__

#include "Buffer.h"

BLADE_NAMESPACE_BEGIN

class BLADE_CORE_API PathUtil
{
private:
	PathUtil();
	~PathUtil();
	
public:
	static const int MAX_PATHNAME;
	
	static const char DOT;					//!< '.'
	static const char SEPERATOR;			//!< '/'
	static const char SLASH;				//!< '/'
	static const char BACKSLASH;			//!< '\\'
	
public:
	static uint32 getFileSize(const std::string &filename);
	static bool   getFileData(Buffer &buff, const std::string &filename, bool bStr = false);
};

BLADE_NAMESPACE_END

#endif