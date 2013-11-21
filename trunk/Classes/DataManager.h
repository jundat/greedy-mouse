
#ifndef __DATA_MANAGER__
#define __DATA_MANAGER__

#define START_LEVEL		1
#define STAR_IN_LEVEL	0
#define IS_TUTORIAL		0


#include "cocos2d.h"
USING_NS_CC;


class DataManager
{
private:
	DataManager();
	static DataManager *_instance;

public:
	static DataManager* GetInstance();

	int		GetCurrenLevel();
	void	SetCurrentLevel(int currentLevel);
	int		GetLevelStar(int level);
	void	SetLevelStar(int level, int star);
	
	~DataManager(void);
};
#endif
