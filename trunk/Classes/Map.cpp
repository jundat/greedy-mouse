#include "Map.h"
#include "ItemData.h"
#include "FileOperation.h"

#include "cocos2d.h"
USING_NS_CC;

#include <sstream>
#include <string>

Map* Map::instance = 0;
int Map::NUMBER_OF_MAP = 20;
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
	
	//all map
	for (int k = 0; k < NUMBER_OF_MAP; ++k)
	{
		//1 map
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

		//////////////////////////////////////////////////////////////////////////
		//READ

 		CCString* fileName = CCString::createWithFormat("map_%d.txt", (k + 1));
 		unsigned long bufferSize = 0;
		unsigned char* data0 = CCFileUtils::sharedFileUtils()->getFileData(fileName->getCString(), "r", &bufferSize);
		char* data1 = (char*) data0;
 		std::string fileData = std::string(data1);
		std::string smallStr;
		
		int counter = 0;

		while(counter < MAP_COL * MAP_ROW) //fileData.length() > 0)
		{
			counter++;

			int beginIndex = fileData.find_first_of('\n');
			smallStr = fileData.substr(0, beginIndex + 1); //pos, len
			fileData = fileData.substr(beginIndex + 1);

			int id, col, row, energy, destcol, destrow, keyid, lockid, lockitemid;
			sscanf(smallStr.c_str(), "%d %d %d %d %d %d %d %d %d\n", &id, &col, &row, &energy, &destcol, &destrow, &keyid, &lockid, &lockitemid);

			ItemData item = ItemData(id, col, row, energy, destcol, destrow, keyid, lockid, lockitemid);

			if (item.col != -1 && item.row != -1)
			{
				map[item.row][item.col] = item;
			}
		}

		listMap[MapCounter++] = map;
	}
}

/*
#pragma region MAP 5
	listMap[MapCounter++] = map_5;
#pragma endregion
*/

