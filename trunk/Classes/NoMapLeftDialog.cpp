#include "NoMapLeftDialog.h"
#include "MainGameScene.h"

#include "cocos2d.h"
USING_NS_CC;


CCScene* NoMapLeftDialog::scene()
{
	CCScene *scene = CCScene::create();
	NoMapLeftDialog *layer = NoMapLeftDialog::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool NoMapLeftDialog::init()
{
	if( !CCLayerColor::init())
	{
		return false;
	}

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);


	mainSpr = CCSprite::create();

	mainSpr->setPosition(CCPointZero);
	this->addChild(mainSpr);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	mainSpr->setPosition(ccp(0, visibleSize.height/2));
	CCActionInterval* move = CCMoveTo::create(2, CCPointZero);
	CCAction* ease = CCEaseElasticOut::create(move);
	mainSpr->runAction(ease);

	return true;
}


void NoMapLeftDialog::GotoMenu(CCObject* sender)
{

	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}
	this->mainGameScene->GotoMenu();
}

void NoMapLeftDialog::Replay(CCObject* sender)
{

	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");

	}
	this->mainGameScene->Replay();
}


void NoMapLeftDialog::InitTarget( MainGameScene* maingamescene, int level)
{
	this->mainGameScene = maingamescene;
	this->currentLevel = currentLevel;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//background
	CCSprite* pSprite = CCSprite::create("noMapLeft.png");

	pSprite->setPosition(ccp(745, visibleSize.height - 370));
	mainSpr->addChild(pSprite, 0);

	//currentLevel
	CCMenuItemImage* menu = CCMenuItemImage::create("buttomMenu.png", "buttomMenuPr.png", this, menu_selector(NoMapLeftDialog::GotoMenu));
	CCMenuItemImage* replay = CCMenuItemImage::create("buttomReset.png", "buttomResetPr.png", this, menu_selector(NoMapLeftDialog::Replay));
	menu->setPosition(ccp(688, visibleSize.height - 449));
	replay->setPosition(ccp(816, visibleSize.height - 449));

	CCMenu* pMenu = CCMenu::create(menu, replay, NULL);
	pMenu->setPosition(CCPointZero);
	mainSpr->addChild(pMenu, 0);
}

bool NoMapLeftDialog::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void NoMapLeftDialog::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}
