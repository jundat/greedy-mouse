#include "Global.h"

#include "MenuScene.h"
#include "CreditsScene.h"
#include "TutScene.h"
#include "CampaignScene.h"

#include "SelectLevelScene.h"

#include "DataManager.h"
#include "AchievementScene.h"
#include <vector>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace std;

USING_NS_CC;


CCScene* MenuScene::scene()
{
	CCScene *scene = CCScene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
	{
		return false;
	}

	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //gốc tọa độ ở góc dưới, bên trái

	//headerMenu
	headerMenu = CCSprite::create("headerMenu.png");
	headerMenu->setPosition(ccp(visibleSize.width/2, visibleSize.height - headerMenu->getContentSize().height/2));
	this->addChild(headerMenu);

	CCSprite* menu_mouse = CCSprite::create("menu_mouse.png");
	menu_mouse->setPosition(ccp(848, visibleSize.height - 141));
	CCAction* rep = CCRepeatForever::create(CCRotateBy::create(4, 360));
	menu_mouse->runAction(rep);
	this->addChild(menu_mouse);

	//menu item...
	start = CCMenuItemImage::create("btPlayNow.png", "btPlayNowPr.png", this, menu_selector(MenuScene::playClicked));
	tutorial = CCMenuItemImage::create("btTutorial.png", "btTutorialPr.png", this, menu_selector(MenuScene::tutorialClicked));

	about = CCMenuItemImage::create("btAbout.png", "btAboutPr.png", this, menu_selector(MenuScene::aboutClicked));
	achievement = CCMenuItemImage::create("btaCHIEVEMENT.png", "btaCHIEVEMENTPR.png", this, menu_selector(MenuScene::achievementClicked));

	CCMenuItem* soundOn = CCMenuItemImage::create("soundOn.png", NULL, NULL);
	CCMenuItem* soundOff = CCMenuItemImage::create("soundOff.png", NULL, NULL);
	sound = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuScene::soundClicked), soundOn, soundOff, NULL);
	if (! G_IsPlaySound)
	{
		sound->setSelectedIndex(1);
	}

	initAnimation();

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(start, tutorial, sound, about, achievement, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	return true;
}


#pragma region MENU ITEM HANDLER



void MenuScene::initAnimation()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //gốc tọa độ ở góc dưới, bên trái

	//
	start->setPosition(-50-visibleSize.width/2, 
		headerMenu->getPositionY() - headerMenu->getContentSize().height/2 - start->getContentSize().height/2);
	tutorial->setPosition(-50-visibleSize.width/2, 
		start->getPositionY() - start->getContentSize().height/2 - tutorial->getContentSize().height/2);
	about->setPosition(-50-visibleSize.width/2, 
		tutorial->getPositionY() - tutorial->getContentSize().height/2 - about->getContentSize().height/2);
	achievement->setPosition(-50-visibleSize.width/2, 
		about->getPositionY() - about->getContentSize().height/2 - achievement->getContentSize().height/2);
	sound->setPosition(-400-sound->getContentSize().width/2,
		sound->getContentSize().height/2);
	//
	float startTime = 0.4f;
	//
	CCActionInterval* acStartMove = CCMoveTo::create(startTime, ccp(visibleSize.width/2, 
		headerMenu->getPositionY() - headerMenu->getContentSize().height/2 - start->getContentSize().height/2));
	CCFiniteTimeAction* easeStartMove = CCEaseOut::create(acStartMove, 1.0f);
	start->runAction(easeStartMove);

	//
	startTime+= 0.2f;
	CCActionInterval* acTutMove = CCMoveTo::create(startTime, ccp(visibleSize.width/2, 
		start->getPositionY() - start->getContentSize().height/2 - tutorial->getContentSize().height/2));
	CCFiniteTimeAction* easeTutMove = CCEaseOut::create(acTutMove, 1.0f);
	tutorial->runAction(easeTutMove);

	//
	startTime+= 0.2f;
	CCActionInterval* acAboutMove = CCMoveTo::create(startTime, ccp(visibleSize.width/2, 
		tutorial->getPositionY() - tutorial->getContentSize().height/2 - about->getContentSize().height/2));
	CCFiniteTimeAction* easeAboutMove = CCEaseOut::create(acAboutMove, 1.0f);
	about->runAction(easeAboutMove);
	
	//
	startTime+= 0.2f;
	CCActionInterval* acRateMeMove = CCMoveTo::create(startTime, ccp(visibleSize.width/2, 
		about->getPositionY() - about->getContentSize().height/2 - achievement->getContentSize().height/2));
	CCFiniteTimeAction* easeRateMeMove = CCEaseOut::create(acRateMeMove, 1.0f);
	achievement->runAction(easeRateMeMove);

	//
	CCActionInterval* acSoundMove = CCMoveTo::create(startTime, ccp(sound->getContentSize().width/2,
		sound->getContentSize().height/2));
	CCFiniteTimeAction* easeSoundMove = CCEaseOut::create(acSoundMove, 1.0f);
	sound->runAction(easeSoundMove);
}


//500
void MenuScene::playClicked(CCObject* pSender)
{
	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}
	CCTransitionScene* transScene = CCTransitionFade::create(0.3, SelectLevelScene::scene());
	CCDirector::sharedDirector()->replaceScene(transScene);
}

//900
void MenuScene::tutorialClicked( CCObject* pSender )
{
	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}
	CCTransitionScene* transScene = CCTransitionFade::create(0.3, TutScene::scene());
	CCDirector::sharedDirector()->replaceScene(transScene);
}

//800
void MenuScene::aboutClicked( CCObject* pSender )
{
	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}
	
	CCTransitionScene* transScene = CCTransitionFade::create(0.3, CreditsScene::scene());
	CCDirector::sharedDirector()->replaceScene(transScene);
}

//600
void MenuScene::achievementClicked( CCObject* pSender )
{
	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}

	vector<int> listAchi;
	listAchi.push_back(1);
	listAchi.push_back(2);
	listAchi.push_back(3);
	listAchi.push_back(4);
	listAchi.push_back(5);
	listAchi.push_back(6);


	CCScene* achi = AchievementScene::scene(listAchi);
	CCTransitionScene* transScene = CCTransitionFade::create(0.3, achi);
	CCDirector::sharedDirector()->replaceScene(transScene);
}

//700
void MenuScene::soundClicked( CCObject* pSender )
{
	G_IsPlaySound = ! G_IsPlaySound;
	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}
}


#pragma endregion