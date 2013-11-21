#ifndef __MAP_H__
#define __MAP_H__



#include "cocos2d.h"
USING_NS_CC;

#include "ItemData.h"

class Map
{
private:
	static Map* instance;
	Map();
	~Map();

	int MapCounter;
	ItemData*** listMap;

public:
	ItemData** GetMap(int map);
	static Map* GetInstance();
	static int NUMBER_OF_MAP;
	static int MAP_COL;
	static int MAP_ROW;
};

#endif //__MAP_H__