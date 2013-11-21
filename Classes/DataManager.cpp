#include "DataManager.h"
DataManager* DataManager::_instance = 0;

DataManager* DataManager::GetInstance()
{
	if(DataManager::_instance == 0)
	{
		_instance = new DataManager();
	}

	return _instance;
}


DataManager::DataManager()
{
}


int	DataManager::GetCurrenLevel()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("CURRENT_LEVEL");
}


//Ko luu so 0
void DataManager::SetCurrentLevel(int currentLevel)
{
	if(currentLevel > this->GetCurrenLevel() )
		CCUserDefault::sharedUserDefault()->setIntegerForKey("CURRENT_LEVEL", currentLevel);
}




int	DataManager::GetLevelStar(int level)
{
// 	char _buf[20];
// 	sprintf_s(_buf, 20, "STAR_LEVEL_%d", level);

	CCString* _buf = CCString::createWithFormat("STAR_LEVEL_%d", level);

	return CCUserDefault::sharedUserDefault()->getIntegerForKey(_buf->getCString());
}


void DataManager::SetLevelStar(int level, int star)
{
	if(level <= this->GetCurrenLevel())
	{
		if(star > GetLevelStar(level))
		{
			//char _buf[20];
			//sprintf_s(_buf, 20, "STAR_LEVEL_%d", level);

			CCString* _buf = CCString::createWithFormat("STAR_LEVEL_%d", level);

			CCUserDefault::sharedUserDefault()->setIntegerForKey(_buf->getCString(), star);
		}
	}
	else
	if(level > this->GetCurrenLevel() )
	{
		//char _buf[20];
		//sprintf_s(_buf, 20, "STAR_LEVEL_%d", level);

		CCString* _buf = CCString::createWithFormat("STAR_LEVEL_%d", level);

		CCUserDefault::sharedUserDefault()->setIntegerForKey(_buf->getCString(), star);
	}
	
}