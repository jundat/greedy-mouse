#include "CreditsScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

CCScene* CreditsScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CreditsScene *layer = CreditsScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CreditsScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
	{
		return false;
	}

	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	}
	//background...

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* pSprite = CCSprite::create("bgCredits.png");
	pSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	this->addChild(pSprite, 0);

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);

	return true;
}

void CreditsScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}
	CCScene* transScene = CCTransitionFade::create(0.3, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(transScene);
}

bool CreditsScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}
