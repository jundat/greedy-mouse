#include "AchievementScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include <string>

using namespace std;
using namespace CocosDenshion;

CCScene* AchievementScene::scene(vector<int> listAchi)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	AchievementScene *layer = AchievementScene::create();
	layer->InitAchievement(listAchi);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool AchievementScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
	{
		return false;
	}


	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	}

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);

	//background...
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* pSprite = CCSprite::create("achivebackground.png");
	pSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	this->addChild(pSprite, 0);

	//achievement
	//when call InitAchievement
	//..

	return true;
}

bool AchievementScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void AchievementScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}
	CCScene* transScene = CCTransitionFade::create(0.3, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(transScene);
}

void AchievementScene::InitAchievement( vector<int> listAchi )
{
// 	this->listAchi = listAchi;
// 	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
// 
// 	//
// 	for (int i = 0; i < listAchi.size(); ++i)
// 	{
// 		int achi = listAchi[i];
// 
// 		char _buf[20];
// 		sprintf_s(_buf, 20, "achi_%d.png", achi);
// 				
// 
// 		CCSprite* spr = CCSprite::create(_buf);
// 		
// 		switch (achi)
// 		{
// 		case 1:
// 			spr->setPosition(ccp(378, visibleSize.height - 230));
// 			break;
// 		case 2:
// 			spr->setPosition(ccp(378, visibleSize.height - 365));
// 			break;
// 		case 3:
// 			spr->setPosition(ccp(378, visibleSize.height - 500));
// 			break;
// 		case 4:
// 			spr->setPosition(ccp(378, visibleSize.height - 635));
// 			break;
// 		case 5:
// 			spr->setPosition(ccp(890, visibleSize.height - 230));
// 			break;
// 		case 6:
// 			spr->setPosition(ccp(890, visibleSize.height - 365));
// 			break;
// 		case 7:
// 			spr->setPosition(ccp(890, visibleSize.height - 500));
// 			break;
// 		case 8:
// 			spr->setPosition(ccp(890, visibleSize.height - 635));
// 			break;
// 		}
// 		
// 		this->addChild(spr);
// 	}
}
