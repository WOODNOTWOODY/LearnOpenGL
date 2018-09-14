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
	static void        formatPath(std::string &path, bool bLower = false);
	static void        normalizeDir(std::string& dir);
	static bool        isLanFile(const std::string& file);
	static bool        isHttpFile(const std::string& file);
	static bool        isDriveOrRoot(const std::string &path);
	static bool	       isEndWithSeperator(const std::string &path);
	static bool        isDir(const std::string &path);
	static bool	       isDirExist(const std::string &dir);
	static uint32      getFileSize(const std::string &filename);
	static bool        getFileData(Buffer &buff, const std::string &filename, bool bStr = false);
	static std::string getFileExt(const std::string &filename, bool bNeedDot = false);
	static std::string getFileDirPath(const std::string &filename);
	static std::string getPureFilename(const std::string& filename, bool bNeedExt = true);
	static std::string getPureDirname(const std::string &dirname);
	static void        enumFiles(std::vector<std::string>& ret, const std::string& rootPath, bool bRecurseSubDirs = false, bool bIncDir = false);
	static bool	       saveFile(const std::string &filename, const void* buff, size_t buffSize, bool bText = false);
	static bool        createDir(const std::string &dir);
	static bool        ensureDir(const std::string &dir);
};

BLADE_NAMESPACE_END

#endif