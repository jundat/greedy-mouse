#include "WinDialog.h"
#include "MainGameScene.h"

#include "cocos2d.h"
USING_NS_CC;


CCScene* WinDialog::scene()
{
	CCScene *scene = CCScene::create();
	WinDialog *layer = WinDialog::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool WinDialog::init()
{
	if( !CCLayerColor::init())
	{
		return false;
	}

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	mainSpr = CCSprite::create();

	//background
	CCSprite* pSprite = CCSprite::create("bgLevelComplete.png");
	pSprite->setPosition(ccp(745, visibleSize.height - 368));
	mainSpr->addChild(pSprite, 0);

	//currentLevel								
	CCMenuItemImage* replay = CCMenuItemImage::create("buttomReset.png", "buttomResetPr.png", this, menu_selector(WinDialog::Replay));
	CCMenuItemImage* menu = CCMenuItemImage::create("buttomMenu.png", "buttomMenuPr.png", this, menu_selector(WinDialog::GotoMenu));
	CCMenuItemImage* next = CCMenuItemImage::create("buttomNext.png", "buttomNextPr.png", this, menu_selector(WinDialog::Next));
	replay->setPosition(ccp(755, visibleSize.height - 502));
	menu->setPosition(ccp(615, visibleSize.height - 502));
	next->setPosition(ccp(892, visibleSize.height - 502));

	CCMenu* pMenu = CCMenu::create(replay, menu, next, NULL);
	pMenu->setPosition(CCPointZero);
	mainSpr->addChild(pMenu, 0);

	//star + text when InitTarget
	//mainSpr->setPosition(CCPointZero);
	this->addChild(mainSpr);

	mainSpr->setPosition(ccp(0, visibleSize.height/2 + mainSpr->getContentSize().height/2));
	CCActionInterval* move = CCMoveTo::create(2, CCPointZero);
	CCAction* ease = CCEaseElasticOut::create(move);
	mainSpr->runAction(ease);

	return true;
}


void WinDialog::GotoMenu(CCObject* sender)
{
	if(G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}
	this->mainGameScene->GotoMenu();
}

void WinDialog::Replay(CCObject* sender)
{
	if(G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}
	
	this->mainGameScene->Replay();
}

void WinDialog::Next( CCObject* sender )
{
	if(G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}
	this->mainGameScene->Next();
}

void WinDialog::InitTarget( MainGameScene* maingamescene, int level, int star)
{
	this->mainGameScene = maingamescene;
	this->currentLevel = currentLevel;
	this->star = star;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//star
	//(605, visibleSize.height - 382)

	//star = 0, 1, 2, 3

	int w=605;
	for (int i = 0; i < 3; ++i)
	{
		CCSprite* sprStar;
		if(this->star > i) {
			sprStar = CCSprite::create("starEnable.png");
		} else {
			sprStar = CCSprite::create("starDisable.png");
		}

		sprStar->setPosition(ccp(w, visibleSize.height - 382));
		mainSpr->addChild(sprStar, 0);

		sprStar->setScale(0.1);

		CCActionInterval* zoomOut = CCScaleTo::create(6, 1, 1);
		CCAction* backin = CCEaseElasticOut::create(zoomOut);
		sprStar->runAction(backin);

		w+=144;
	}
}

bool WinDialog::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void WinDialog::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

