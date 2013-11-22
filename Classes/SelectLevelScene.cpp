
#include "SelectLevelScene.h"
#include "cocos2d.h"
#include "MenuScene.h"
#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
#include "Map.h"
#include "DataManager.h"

USING_NS_CC;
using namespace CocosDenshion;


CCScene* SelectLevelScene::scene()
{
	CCLog("SelectLevelScene");
	CCScene *scene = CCScene::create();
	SelectLevelScene *layer = SelectLevelScene::create();
	scene->addChild(layer);
	return scene;
}

bool SelectLevelScene::init()
{
	if (!CCLayerColor::init())
	{
		return false;
	}
	
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();

	//background
	CCSprite* sprBackground = CCSprite::create("selectLevelBg.png");
	sprBackground->setPosition(ccp(vs.width/2, vs.height/2));
	this->addChild(sprBackground);

	//buffer
	mainSprite = CCSprite::create();
	mainSprite->setPosition(ccp(vs.width/2, vs.height/2));
	this->addChild(mainSprite);

	//level pack
	int maxlevel = Map::NUMBER_OF_MAP;
	int numberOfColum = 5;
	int numberOfRow = 4;

	int currentLevel = DataManager::GetInstance()->GetCurrenLevel();
	CCSprite* sprLevel = CCSprite::create("lockLevel.png");
	int levelCouter = 0;
	float dx = 80;
	float dy = 50;
	float top = vs.height/2 + (numberOfRow / 2.0 - 0.5)*(sprLevel->getContentSize().height + dy) / 2.0;
	float left = vs.width/2 - (numberOfColum / 2.0 - 0.5)*(sprLevel->getContentSize().width + dx) / 2.0;
	float deltax = sprLevel->getContentSize().width + dx;
	float deltay = sprLevel->getContentSize().height + dy;

	for (int i = 0; i < numberOfRow; ++i)
	{
		for (int j = 0; j < numberOfColum; ++j)
		{
			int lv = i * numberOfColum + j;
			float x = left + j * deltax;
			float y = top - i * deltay;

			if (lv < currentLevel) //played
			{
				sprLevel = CCSprite::create("unlockLevel.png");
				sprLevel->setPosition(ccp(x, y));
				mainSprite->addChild(sprLevel);

				int star = DataManager::GetInstance()->GetLevelStar(i + 1);
				CCString* _buf = CCString::createWithFormat("%dStar.png", star); //1 sai lầm cực kỳ lớn khi gõ tên "Star" thành "star"

				CCSprite* sprStar = CCSprite::create(_buf->getCString());
				sprStar->setPosition(ccp(x, y));
				mainSprite->addChild(sprStar); //tag = i
			}
			else if(lv == currentLevel) //current level
			{
				sprLevel = CCSprite::create("unlockLevel.png");
				sprLevel->setPosition(ccp(x, y));
				mainSprite->addChild(sprLevel);

				CCSprite* sprStar = CCSprite::create("0Star.png");
				sprStar->setPosition(ccp(x, y));
				mainSprite->addChild(sprStar); //tag = i
			}
			else //draw locked level
			{
				sprLevel = CCSprite::create("lockLevel.png");
				sprLevel->setPosition(ccp(x, y));
				mainSprite->addChild(sprLevel);
			}
		}
	}
	
	return true;
}
