#include "CoreStd.h"
#include "PathUtil.h"
#include <direct.h>
#include <dirent.h>
#include <Shlwapi.h>

#if (BLADE_PLATFORM == BLADE_PLATFORM_WINDOWS)
#	include <direct.h>
#	include <dirent.h>
#   include <Shlwapi.h>
#pragma comment( lib, "Shlwapi.lib")
#else
#	include <unistd.h>
#	include <sys/stat.h>
#	include <dirent.h>
#endif

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

bool PathUtil::isHttpFile(const std::string &file)
{
	std::string tempFile = file;
	std::transform(tempFile.begin(), tempFile.end(), tempFile.begin(), tolower);

	std::string key = "http:";
	size_t keyLen = key.length();

	if (tempFile.length() < keyLen)
	{
		return false;
	}

	return (tempFile.substr(0, keyLen) == key);
}

bool PathUtil::isLanFile(const std::string &file)
{
	std::string tempFile = file;
	char *buf = &(*tempFile.begin());
	while (*buf)
	{
		if (*buf == BACKSLASH)
			*buf = SEPERATOR;
		++buf;
	}

	std::string key = "//";
	size_t keyLen = key.length();

	if (tempFile.length() < keyLen)
	{
		return false;
	}

	return (tempFile.substr(0, keyLen) == key);
}

void PathUtil::formatPath(std::string &file, bool bLower)
{
	if (PathUtil::isHttpFile(file))
	{
		char *buf = &(*file.begin());
		while (*buf)
		{
			if (*buf == BACKSLASH)
				*buf = SEPERATOR;
			++buf;
		}

		bool bReplaced = false;
		do
		{
			bReplaced = false;
			size_t pos = file.find("//", 0);
			if (pos != std::string::npos)
			{
				file.replace(pos, file.size(), "/");
				bReplaced = true;
			}
		} while (bReplaced);

		std::string tag1 = "http:/";
		std::string tag2 = "http://";
		size_t pos = file.find(tag1, 0);
		while (pos != std::string::npos)
		{
			file.replace(pos, tag1.size(), tag2);
			pos = file.find(tag1, pos + tag2.size());
		}
	}
	else
	{
		bool bLan = false;
		bLan = isLanFile(file);

		char *buf = &(*file.begin());
		while (*buf)
		{
			if (*buf == BACKSLASH)
				*buf = SEPERATOR;
			++buf;
		}

		bool bReplaced = false;
		do
		{
			bReplaced = false;
			size_t pos = file.find("//", 0);
			if (pos != std::string::npos)
			{
				file.replace(pos, file.size(), "/");
				bReplaced = true;
			}
		} while (bReplaced);

		if (bLan)
		{
			file = SLASH + file;
		}
	}

	if (bLower)
	{
		std::transform(file.begin(), file.end(), file.begin(), tolower);
	}
}

void PathUtil::normalizeDir(std::string& dir)
{
	if (!dir.empty())
	{
		for (size_t i = 0; i < dir.size(); i++)
		{
			if (dir[i] == '\\') dir[i] = SEPERATOR;
		}

		char c = dir[dir.size() - 1];
		if ((c != ':') && (c != SEPERATOR))
		{
			dir.append(1, SEPERATOR);
		}
	}
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

std::string PathUtil::getFileExt(const std::string &filename, bool bNeedDot)
{
	size_t pos = filename.find_last_of(DOT);
	if (pos == std::string::npos)
	{
		return "";
	}

	if (!bNeedDot)
		++pos;

	return filename.substr(pos);
}

std::string PathUtil::getFileDirPath(const std::string &filename)
{
	std::string path = filename;
	formatPath(path);
	size_t pos = path.find_last_of(SEPERATOR);
	if (pos == std::string::npos)
	{
		return "";
	}
	path = path.substr(0, pos + 1);

	return path;
}

std::string PathUtil::getPureFilename(const std::string &filename, bool bNeedExt)
{
	std::string pureFilename = filename;

	if (!bNeedExt)
	{
		size_t dotPos = pureFilename.find_last_of(DOT);
		if (dotPos != std::string::npos)
		{
			pureFilename = pureFilename.substr(0, dotPos);
		}
	}

	char *buf = &(*pureFilename.begin());
	while (*buf)
	{
		if (*buf == BACKSLASH)
			*buf = SEPERATOR;
		++buf;
	}

	size_t pos = pureFilename.find_last_of(SEPERATOR);
	if (pos != std::string::npos)
	{
		pureFilename = pureFilename.substr(pos + 1);
	}

	return pureFilename;
}

std::string PathUtil::getPureDirname(const std::string &dirname)
{
	if (!isDir(dirname))
		return "";

	std::string pureDirname = dirname;
	pureDirname = pureDirname.substr(0, pureDirname.length() - 1);

	char *buf = &(*pureDirname.begin());
	while (*buf)
	{
		if (*buf == BACKSLASH)
			*buf = SLASH;
		++buf;
	}

	size_t pos = pureDirname.find_last_of(SEPERATOR);
	if (pos != std::string::npos)
	{
		pureDirname = pureDirname.substr(pos + 1);
	}

	pureDirname += SEPERATOR;

	return pureDirname;
}

static void _enumFilesInDir(std::vector<std::string>& ret, const std::string& rootPath, bool bRecurseSubDirs, bool bIncDir)
{
	DIR *pDir;
	struct dirent *pDirInfo;

	// open dirent directory
	if ((pDir = opendir(rootPath.c_str())) == NULL)
	{
		return;
	}

	// read all files in this dir
	while ((pDirInfo = readdir(pDir)) != NULL)
	{
		if (pDirInfo->d_type == DT_REG)
		{
			ret.push_back(rootPath + pDirInfo->d_name);
		}
		else if (pDirInfo->d_type == DT_DIR)
		{
			if (pDirInfo->d_name[0] == '.') continue; // such as . .. .svn

			std::string tmpPath(rootPath + pDirInfo->d_name);
			tmpPath += PathUtil::SEPERATOR;
			if (bIncDir)
			{
				ret.push_back(tmpPath);
			}
			if (bRecurseSubDirs)
			{
				_enumFilesInDir(ret, tmpPath, bRecurseSubDirs, bIncDir);
			}
		}
	}
	closedir(pDir);
}

void PathUtil::enumFiles(std::vector<std::string>& ret, const std::string& rootPath, bool bRecurseSubDirs, bool bIncDir)
{
	std::string path(rootPath);
	normalizeDir(path);
	_enumFilesInDir(ret, path, bRecurseSubDirs, bIncDir);
}

bool PathUtil::isEndWithSeperator(const std::string &path)
{
	if (!path.length())
		return false;

	char c = path[path.length() - 1];
	return c == SLASH || c == BACKSLASH;
}

bool PathUtil::isDir(const std::string &path)
{
	if (path.length() == 0)
		return false;

	return isEndWithSeperator(path);
}

bool PathUtil::isDriveOrRoot(const std::string &path)
{
	if ((path.length() == 1 && path[0] == SEPERATOR) ||		// unix/linux mount point
		((path.length() == 2 || path.length() == 3) && path[1] == ':')	// windows drive, like c:/
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PathUtil::isDirExist(const std::string &dir)
{
	if (isDriveOrRoot(dir))
		return true;

	std::string tempPath = dir;
	if (isEndWithSeperator(tempPath))
	{
		tempPath = tempPath.substr(0, tempPath.length() - 1);
	}

	const char *filename = tempPath.c_str();

#if (BLADE_PLATFORM == BLADE_PLATFORM_WINDOWS)
	return (PathFileExistsA(filename) != 0);
#else
	struct stat st;
	/* get dirent status */
	if (stat(filename, &st) == -1)
	{
		return false;
	}
	return S_ISDIR(st.st_mode);
#endif
}

bool PathUtil::ensureDir(const std::string &dir)
{
	//if(!IsDir(dir))
	//	return false;

	if (!isDirExist(dir))
	{
		if (!createDir(dir))
			return false;
	}

	return true;
}

#if (BLADE_PLATFORM == BLADE_PLATFORM_WINDOWS)
bool PathUtil::createDir(const std::string &_dir)
{
	if (_dir.empty()) return false;

	std::string dir;
	const char* p = _dir.c_str();
	while (*p)
	{
		if (('\\' == *p) || ('/' == *p))
		{
			if (':' != *(p - 1) && !isDirExist(dir))
			{
				if (!CreateDirectoryA(dir.c_str(), NULL))
				{
					return false;
				}
			}
		}
		dir.append(1, *p++);
	}
	if (('\\' != *(p - 1)) && ('/' != *(p - 1)) && !isDirExist(dir))
	{
		if (!CreateDirectoryA(dir.c_str(), NULL))
		{
			return false;
		}
	}
	return true;
}
#else
bool PathUtil::createDir(const std::string &_dir)
{
	if (_dir.empty()) return false;

	std::string dir;
	const char* p = _dir.c_str();
	while (*p)
	{
		if ('/' == *p)
		{
			if (!dir.empty() && !isDirExist(dir))
			{
				if (mkdir(dir.c_str(), 0755) != 0)
				{
					return false;
				}
			}
		}
		dir.append(1, *p++);
	}

	if (('/' != *(p - 1)) && !isDirExist(dir))
	{
		if (mkdir(dir.c_str(), 0755) != 0)
		{
			return false;
		}
	}
	return true;
}
#endif

bool PathUtil::saveFile(const std::string &filename, const void* buff, size_t buffSize, bool bText)
{
	std::string::size_type pos = filename.find_last_of(SEPERATOR);
	if (pos != std::string::npos)
	{
		ensureDir(filename.substr(0, pos + 1));
	}

	const char *mode = bText ? "w" : "wb";
	FILE *pFile = fopen(filename.c_str(), mode);
	if (!pFile)
	{
		return false;
	}

	bool bRet = true;
	if (fwrite(buff, 1, buffSize, pFile) != buffSize)
	{
		bRet = false;
	}
	fclose(pFile);

	return bRet;
}

BLADE_NAMESPACE_END
