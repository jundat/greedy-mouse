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
	if(currentLevel > this->GetCurrenLevel() ) {
		CCUserDefault::sharedUserDefault()->setIntegerForKey("CURRENT_LEVEL", currentLevel);
		CCUserDefault::sharedUserDefault()->flush();
	}
}




int	DataManager::GetLevelStar(int level)
{
	CCString* _buf = CCString::createWithFormat("STAR_LEVEL_%d", level);

	return CCUserDefault::sharedUserDefault()->getIntegerForKey(_buf->getCString());
}


void DataManager::SetLevelStar(int level, int star)
{
	if(level <= this->GetCurrenLevel())
	{
		if(star > GetLevelStar(level))
		{
			CCString* _buf = CCString::createWithFormat("STAR_LEVEL_%d", level);

			CCUserDefault::sharedUserDefault()->setIntegerForKey(_buf->getCString(), star);
			CCUserDefault::sharedUserDefault()->flush();
		}
	}
	else
	if(level > this->GetCurrenLevel() )
	{
		CCString* _buf = CCString::createWithFormat("STAR_LEVEL_%d", level);

		CCUserDefault::sharedUserDefault()->setIntegerForKey(_buf->getCString(), star);
		CCUserDefault::sharedUserDefault()->flush();
	}
	
}