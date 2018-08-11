#include "CoreStd.h"
#include "PathUtil.h"
#include <direct.h>
#include <dirent.h>
#include <Shlwapi.h>

BLADE_NAMESPACE_BEGIN

const int PathUtil::MAX_PATHNAME = 511;

const char PathUtil::DOT = '.';
const char PathUtil::SEPERATOR = '/';
const char PathUtil::SLASH = '/';
const char PathUtil::BACKSLASH = '\\';

//////////////////////////////////////////////////////////////////////////

PathUtil::PathUtil()
{
}

PathUtil::~PathUtil()
{
}

uint32 PathUtil::getFileSize(const std::string &filename)
{
	struct stat st;

	/* get dirent status */
	if(stat(filename.c_str(), &st) == -1)
	{
		return false;
	}

	/* if dirent is a directory */
	if(S_ISDIR(st.st_mode))
	{
		return false;
	}

	return (uint32)st.st_size;
}

bool PathUtil::getFileData(Buffer &buff, const std::string &filename, bool bStr)
{
	FILE *pFile = fopen(filename.c_str(), "rb");
	if(!pFile)
	{
		return false;
	}

	fseek(pFile, 0, SEEK_END);
	uint32 size = (uint32)ftell(pFile);
	if (!size)
	{
		// file opened, but zero-sized
		fclose(pFile);
		return false;
	}
	
	fseek(pFile, 0, SEEK_SET);

	uint32 buffSize = (bStr ? size + 1 : size);
	buff.allocate(buffSize);
	fread(buff.data(), 1, (size_t)size, pFile);

	if(bStr)
	{
		buff.data()[size] = 0;
	}
	
	fclose(pFile);

	return true;
}

BLADE_NAMESPACE_END
