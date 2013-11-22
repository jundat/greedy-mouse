
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
	
	//touch init...
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);
	isMoved = false;

	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();

	//background
	CCSprite* sprBackground = CCSprite::create("selectLevelBg.png");
	sprBackground->setPosition(ccp(vs.width/2, vs.height/2));
	this->addChild(sprBackground);

	//buffer
	mainSprite = CCSprite::create();
	mainSprite->setPosition(CCPointZero);
	this->addChild(mainSprite);
	
	//level pack
	int maxlevel = Map::NUMBER_OF_MAP;
	int numberOfColum = 5;
	int numberOfRow = 4;

	int currentLevel = DataManager::GetInstance()->GetCurrenLevel() - 1;
	CCSprite* sprLevel = CCSprite::create("lockLevel.png");
	int levelCouter = 0;
	float dx = 60;
	float dy = 40;
	float w = sprLevel->getContentSize().width;
	float h = sprLevel->getContentSize().height;
	float top = vs.height/2 + (numberOfRow/2.0-0.5) * h + (numberOfRow-1)/2.0 * dy;
	float left = vs.width/2 - (numberOfColum/2.0 - 0.5) * w - (numberOfColum-1)/2.0 * dx;
	float deltax = w + dx;
	float deltay = h + dy;
	
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
				mainSprite->addChild(sprLevel, 0, lv);

				int star = DataManager::GetInstance()->GetLevelStar(lv + 1);
				CCString* _buf = CCString::createWithFormat("%dStar.png", star); //1 sai lầm cực kỳ lớn khi gõ tên "Star" thành "star"

				CCSprite* sprStar = CCSprite::create(_buf->getCString());
				sprStar->setPosition(ccp(x, y));
				mainSprite->addChild(sprStar); //tag = i
			}
			else if(lv == currentLevel) //current level
			{
				sprLevel = CCSprite::create("unlockLevel.png");
				sprLevel->setPosition(ccp(x, y));
				mainSprite->addChild(sprLevel, 0, lv);

				CCSprite* sprStar = CCSprite::create("0Star.png");
				sprStar->setPosition(ccp(x, y));
				mainSprite->addChild(sprStar); //tag = i
			}
			else //draw locked level
			{
				sprLevel = CCSprite::create("lockLevel.png");
				sprLevel->setPosition(ccp(x, y));
				mainSprite->addChild(sprLevel, 0, lv);
			}
		}
	}
	
	return true;
}

bool SelectLevelScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	isMoved = false;
	return true;
}

void SelectLevelScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	isMoved = true;
}

void SelectLevelScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (isMoved)
	{
		isMoved = false;
		return;
	}
	//
	CCArray* children = mainSprite->getChildren();
	for (int i = 0; i < children->count(); ++i)
	{
		CCSprite* spr = (CCSprite*)children->objectAtIndex(i);
		int level = spr->getTag();

		if(level >= 0 && spr->boundingBox().containsPoint(pTouch->getLocation()))
		{
			CCLOG("Select level %d", level);
			GotoPlay(level);
			break;
		}
	}
}

void SelectLevelScene::GotoPlay( int level )
{
	CCLOG("[info] Start create MainGameScene");
	CCScene* maingame = MainGameScene::scene(level);
	CCLOG("[info] End create MainGameScene");

	CCScene* transScene = CCTransitionFade::create(0.3, maingame);
	CCDirector::sharedDirector()->replaceScene(transScene);
}