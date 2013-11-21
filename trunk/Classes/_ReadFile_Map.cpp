#include "Map.h"
#include "ItemData.h"
#include "FileOperation.h"

#include "cocos2d.h"
USING_NS_CC;

#include <sstream>
#include <string>
using namespace std;

Map* Map::instance = 0;
int Map::NUMBER_OF_MAP = 11;
int Map::MAP_COL = 11;
int Map::MAP_ROW = 8;



Map* Map::GetInstance()
{
	if(instance == 0)
	{
		instance = new Map();
	}

	return instance;
}

ItemData** Map::GetMap(int map)
{
	return listMap[map];
}

Map::Map()
{
	MapCounter = 0;
	listMap = new ItemData**[NUMBER_OF_MAP];
	
	for (int i = 0; i < NUMBER_OF_MAP; ++i)
	{
		//char _filename[20];
		//sprintf_s(_filename, 20, "map_%d.txt", (i+1));

		CCString* _filename = CCString::createWithFormat("map_%d.txt", (i+1));


		CCFileUtils* reader = CCFileUtils::sharedFileUtils();
		std::string fullPath = reader->fullPathForFilename(_filename->getCString());

		FILE *fp = fopen(fullPath.c_str(), "r");
		char* buf = new char[8192];

		if (! fp)
		{
			CCLOG("Can not open file %s", fullPath.c_str());
			CCMessageBox("Can not read map :(", "ERROR");
			break;
		}

		ItemData** map;
		map = new ItemData*[MAP_ROW];
		for (int i = 0; i < MAP_ROW; ++i)
		{
			map[i] = new ItemData[MAP_COL];
			for (int j = 0; j < MAP_COL; ++j)
			{
				map[i][j] = ItemData();
			}
		}
				
		while(!feof(fp))
		{
			ItemData item = ItemData();

			unsigned long size = 8 * 1024;
			unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(_filename->getCString(), "r", &size);
			string s(data);
 			stringstream ss(s);

			int i = 0;
			//ss >> i;


			fscanf(fp, "%d, %d, %d, %d, %d, %d, %d, %d, %d\n",
				&item.id, &item.col, &item.row, &item.energy,
				&item.destCol, &item.destRow, &item.keyId, &item.lockId,
				&item.lockItemId);

			if (item.col != -1 && item.row != -1)
			{
				map[item.row][item.col] = item;
			}
		}

		listMap[MapCounter++] = map;
		fclose(fp);
	}
	
#pragma endregion

}

/*

#pragma region MAP 5
	
	listMap[MapCounter++] = map_5;
#pragma endregion

*/

