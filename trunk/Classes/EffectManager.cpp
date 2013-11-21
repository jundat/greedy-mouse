#include "EffectManager.h"

#include "cocos2d.h"
USING_NS_CC;


CCScene* EffectManager::scene()
{
    CCScene *scene = CCScene::create();
    EffectManager *layer = EffectManager::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool EffectManager::init()
{
	if( !CCLayerColor::init())
	{
		return false;
	}

    return true;
}


void EffectManager::InitWithTarget( CCLayer* parentLayer)
{
	this->parentLayer = parentLayer;
	parentLayer->addChild(this, 99);
}

void EffectManager::AddStartEff( CCPoint p )
{
	CCSprite* spr = CCSprite::create("effStart.png");
	CCAction* zoomInOut = CCRepeatForever::create(CCSequence::create(
		CCScaleBy::create(0.5f, 1.4f, 1.4f),
		CCScaleBy::create(0.5f, 1.4f, 1.4f)->reverse(),
		NULL));

	spr->setPosition(p);
	this->addChild(spr);
	this->listStartSpr.push_back(spr);
	spr->runAction(zoomInOut);
}

void EffectManager::AddFinishEff( CCPoint p )
{
	CCSprite* spr = CCSprite::create("effFinish.png");
	CCActionInterval* blink = CCBlink::create(2, 2);
	CCAction* repeat = CCRepeatForever::create(blink);

	spr->setPosition(p);
	this->addChild(spr);
	this->listFinishSpr.push_back(spr);
	spr->runAction(repeat);
}

void EffectManager::RemoveAllStartEff()
{
	for (int i = 0; i < listStartSpr.size(); ++i)
	{
		this->removeChild(listStartSpr[i]);
	}
}

void EffectManager::RemoveAllFinishEff()
{
	for (int i = 0; i < listFinishSpr.size(); ++i)
	{
		this->removeChild(listFinishSpr[i]);
	}
}

void EffectManager::RemoveAllEff()
{
	this->removeAllChildren();
}

void EffectManager::FadeOutIn()
{
	CCSprite* black = CCSprite::create("black.png");

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize size = black->getContentSize();
	black->setScaleX(visibleSize.width/size.width);
	black->setScaleY(visibleSize.height/size.height);

	CCAction* fadeout = CCFadeOut::create(0.5);
	CCAction* fadein = CCFadeIn::create(0.5);
	
	black->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	
	black->runAction(fadein);
	black->runAction(fadeout);

	this->addChild(black);
}
