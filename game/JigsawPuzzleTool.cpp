#include "StdAfx.h"
#include <cstdio>
#include "CoreStd.h"
#include "util/PathUtil.h"
#include "image/Image.h"
#include "math/Vec4.h"
#include <thread>
#include <mutex>

USING_NAMESPACE_BLADE;

std::map<uint32, uint32> charId2NumMap;
std::map<uint32, std::map<uint32, Vec4i>> charId2PieceOffsetMap;
std::map<uint32, std::vector<std::pair<uint32, Vec4i>>> charId2PieceOrder;

static int cmp(const void *a, const void *b)
{
	std::pair<uint32, Vec4ui>* pa = (std::pair<uint32, Vec4ui> *)(a);
	std::pair<uint32, Vec4ui>* pb = (std::pair<uint32, Vec4ui> *)(b);
	int dax = pa->second.z - pa->second.x;
	int day = pa->second.w - pa->second.y;
	int dbx = pb->second.z - pb->second.x;
	int dby = pb->second.w - pb->second.y;
	if (dax > dbx)
	{
		return -1;
	}
	else if (dax < dbx)
	{
		return 1;
	}
	else
	{
		if (day > dby)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
}

struct ThreadTask
{
	std::list<std::string>* files;
	std::mutex   mutex;
};

static void thread_task(ThreadTask* task)
{
	while (true)
	{
		std::string file;
		task->mutex.lock();
		if (!task->files->empty())
		{
			file = task->files->front();
			task->files->pop_front();
		}
		task->mutex.unlock();
		if (file.empty()) return;

		std::string fileName = PathUtil::getPureFilename(file);
		std::string dirName = PathUtil::getFileDirPath(file);
		size_t firstOffset = fileName.find("_");
		size_t lastOffset = fileName.find("_k.png");
		if (lastOffset != std::string::npos)
		{
			printf("begin task:%s\n", file.c_str());
			uint32 charId, pieceId;
			std::string str1 = fileName.substr(1, firstOffset - 1);
			std::string str2 = fileName.substr(firstOffset + 1, lastOffset - firstOffset - 1);
			sscanf(str1.c_str(), "%u", &charId);
			sscanf(str2.c_str(), "%u", &pieceId);

			task->mutex.lock();
			auto ptr = charId2NumMap.find(charId);
			if (ptr != charId2NumMap.end())
			{
				charId2NumMap[charId] = ptr->second + 1;
			}
			else
			{
				charId2NumMap[charId] = 1;

				std::map<uint32, Vec4i> pieceId2Offset;
				charId2PieceOffsetMap[charId] = pieceId2Offset;
			}
			task->mutex.unlock();

			Buffer buff2;
			char tempPath[256];
			sprintf(tempPath, "%sworld%u.png", dirName.c_str(), charId);
			PathUtil::getFileData(buff2, tempPath);
			ImageFormat imgFmt = Image::getImageFormat(fileName);
			Image *pImage = Image::createFromMemory(buff2, imgFmt, false);

			Buffer buff3;
			sprintf(tempPath, "%sw%u_%u_b.png", dirName.c_str(), charId, pieceId);
			PathUtil::getFileData(buff3, tempPath);
			Image *pBackgroundImage = Image::createFromMemory(buff3, imgFmt, false);

			float scaleWidth = (float)pImage->getWidth() / (float)pBackgroundImage->getWidth();
			float scaleHeight = (float)pImage->getHeight() / (float)pBackgroundImage->getHeight();
			
			Buffer buff1;
			PathUtil::getFileData(buff1, file);
			Image *pTemplateImage = Image::createFromMemory(buff1, imgFmt, false);
			pTemplateImage->scale(pTemplateImage->getWidth() * scaleWidth, pTemplateImage->getHeight() * scaleHeight, IMGFILTER_BILINEAR);

			float minMatchDegree = Math::MAX_FLOAT;
			Vec4i box(0, 0, 0, 0);
			/*for (int i = 0; i < pImage->getWidth(); ++i)
			{
				for (int j = 0; j < pImage->getHeight(); ++j)
				{
					bool flag = false;
					Color c = pImage->getColor(i, j);
					if (Math::IsNotEqual(c.a, 0.0f))
					{
						for (int m = -1; m <= 1; ++m)
						{
							for (int n = -1; n <= 1; ++n)
							{
								if (m != 0 || n != 0)
								{
									int di = i + m;
									int dj = j + n;
									if (di >= 0 && di < pImage->getWidth() && dj >= 0 && dj < pImage->getHeight())
									{
										Color c = pImage->getColor(i + m, j + n);
										if (Math::IsNotEqual(c.a, 0.0f))
										{
											flag = true;
											break;
										}
									}
								}
							}

							if (flag) break;
						}
					}

					if (flag)
					{
						if (i < box.x) box.x = i;
						if (i > box.z) box.z = i;
						if (j < box.y) box.y = j;
						if (j > box.w) box.w = j;
					}
				}
			}*/

			for (int i = 0; i <= (pImage->getWidth() - pTemplateImage->getWidth()); ++i)
			{
				for (int j = 0; j <= (pImage->getHeight() - pTemplateImage->getHeight()); ++j)
				{
					float matchDegree = 0.0f;
					for (int m = 0; m < pTemplateImage->getWidth(); ++m)
					{
						for (int n = 0; n < pTemplateImage->getHeight(); ++n)
						{
							Color c1 = pImage->getColor(i + m, j + n);
							Color c2 = pTemplateImage->getColor(m, n);
							float gray1 = 0.2989 * c1.r + 0.5870 * c1.g + 0.1140 * c1.b;
							float gray2 = 0.2989 * c2.r + 0.5870 * c2.g + 0.1140 * c2.b;
							matchDegree += abs(gray1 - gray2);
						}
					}

					if (matchDegree < minMatchDegree)
					{
						minMatchDegree = matchDegree;
						box.x = i;
						box.y = j;
						box.z = pTemplateImage->getWidth();
						box.w = pTemplateImage->getHeight();
					}
				}
			}

			task->mutex.lock();
			charId2PieceOffsetMap[charId][pieceId] = box;
			task->mutex.unlock();

			pImage->destroy();
			pTemplateImage->destroy();

			printf("end task:%s\n", file.c_str());
		}
	}
}

static bool doTask(ThreadTask* task)
{
	int threadCount = 2 * (int)std::thread::hardware_concurrency();
	if (threadCount > (int)task->files->size()) threadCount = (int)task->files->size();

	std::thread** threads = new std::thread*[threadCount];
	for (int i = 0; i < threadCount; i++)
	{
		threads[i] = new std::thread(thread_task, task);
	}
	printf("spawning threads: %d\n", threadCount);
	for (int i = 0; i < threadCount; i++)
	{
		threads[i]->join();
		delete threads[i];
	}
	delete[] threads;

	return true;
}

int main(int argc, char *argv[])
{
	std::vector<std::string> files;
	std::list<std::string> fileList;

	PathUtil::enumFiles(files, "../../resource"/*"../../trunk/main/UIProject/assets"*/, true, false);
	for (auto it = files.begin(); it != files.end(); ++it)
	{
		fileList.push_back(*it);
	}
	
	ThreadTask task;
	task.files = &fileList;
	doTask(&task);

	for (auto it1 = charId2PieceOffsetMap.begin(); it1 != charId2PieceOffsetMap.end(); ++it1)
	{
		std::vector<std::pair<uint32, Vec4i>> order;
		charId2PieceOrder[it1->first] = order;
		for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
		{
			charId2PieceOrder[it1->first].push_back(std::make_pair(it2->first, it2->second));
		}
		std::qsort(&charId2PieceOrder[it1->first][0], charId2PieceOrder[it1->first].size(), sizeof(std::pair<uint32, Vec4ui>), cmp);
	}

	char temp[256];
	std::string tempStr;
	Buffer saveBuff;
	saveBuff.allocate(10 * 1024);
	tempStr = "local charId2PieceNum = \n{\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());
	for (auto it = charId2NumMap.begin(); it != charId2NumMap.end(); ++it)
	{
		sprintf(temp, "\t[%u] = %u,\n", it->first, it->second);
		tempStr = temp;
		saveBuff.write(tempStr.c_str(), tempStr.size());
	}
	tempStr = "}\n\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());

	tempStr = "local charId2PieceOffset = \n{\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());
	for (auto it1 = charId2PieceOffsetMap.begin(); it1 != charId2PieceOffsetMap.end(); ++it1)
	{
		sprintf(temp, "\t[%u] = {", it1->first);
		tempStr = temp;
		saveBuff.write(tempStr.c_str(), tempStr.size());
		for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
		{
			sprintf(temp, "[%u] = {%u, %u}, ", it2->first, 2 * it2->second.x - 1, 2 * it2->second.y - 1);
			tempStr = temp;
			saveBuff.write(tempStr.c_str(), tempStr.size());
		}
		tempStr = "},\n";
		saveBuff.write(tempStr.c_str(), tempStr.size());
	}
	tempStr = "}\n\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());

	tempStr = "local charId2PieceOrder = \n{\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());
	for (auto it1 = charId2PieceOrder.begin(); it1 != charId2PieceOrder.end(); ++it1)
	{
		sprintf(temp, "\t[%u] = {", it1->first);
		tempStr = temp;
		saveBuff.write(tempStr.c_str(), tempStr.size());
		for (int i = 0; i < it1->second.size(); ++i)
		{
			std::pair<uint32, Vec4i> pa = it1->second.at(i);
			if (i < it1->second.size() - 1)
			{
				sprintf(temp, "%u, ", pa.first);
				tempStr = temp;
				saveBuff.write(tempStr.c_str(), tempStr.size());
			}
			else
			{
				sprintf(temp, "%u", pa.first);
				tempStr = temp;
				saveBuff.write(tempStr.c_str(), tempStr.size());
			}
		}
		tempStr = "},\n";
		saveBuff.write(tempStr.c_str(), tempStr.size());
	}
	tempStr = "}\n\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());

	tempStr = "local t = {}\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());
	tempStr = "t.charId2PieceNum = charId2PieceNum\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());
	tempStr = "t.charId2PieceOffset = charId2PieceOffset\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());
	tempStr = "t.charId2PieceOrder = charId2PieceOrder\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());
	tempStr = "return t\n";
	saveBuff.write(tempStr.c_str(), tempStr.size());

	PathUtil::saveFile("character_config.lua", saveBuff.data(), saveBuff.offset(), true);

	return 0;
}