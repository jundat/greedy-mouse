
#include "cocos2d.h"
USING_NS_CC;
#define FILE_BUFFER_SIZE  8192 //4096 //1024

#include "FileOperation.h"
using namespace std;


bool FileOperation::SaveFile(const char* relativePath, const char* content)
{
	CCFileUtils* reader = CCFileUtils::sharedFileUtils();
	std::string fullPath = reader->fullPathForFilename(relativePath);

	FILE *fp = fopen(fullPath.c_str(), "a");

	if (! fp)
	{
		CCLOG("Can not create file %s", fullPath.c_str());
		return false;
	}

	fputs(content, fp);
	fclose(fp);
	return true;
}

char* FileOperation::ReadFile(const char* relativePath)
{
	CCFileUtils* reader = CCFileUtils::sharedFileUtils();
	std::string fullPath = reader->fullPathForFilename(relativePath);

//	unsigned char* data = CCFileUtils::getFileData(relativePath);

	FILE *fp = fopen(fullPath.c_str(), "w");
	char* buf = new char[FILE_BUFFER_SIZE];

	if (! fp)
	{
		CCLOG("Can not open file %s", fullPath.c_str());
		return 0;
	}

	//while(!feof(fp))
	{
		fgets(buf, FILE_BUFFER_SIZE, fp);
	}

	CCLOG("Read ok file: %s", relativePath);
	fclose(fp);
	return buf;
}


