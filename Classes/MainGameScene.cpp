#include "MainGameScene.h"
#include "AppMacros.h"
#include "MenuScene.h"
#include "CampaignScene.h"

#include "WinDialog.h"
#include "LoseDialog.h"
#include "SelectLevelScene.h"
#include "NoMapLeftDialog.h"


//level count from 1
CCScene* MainGameScene::scene(int level)
{
    CCScene *scene = CCScene::create();
    MainGameScene *layer = MainGameScene::create();
	layer->initLevel(level);
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MainGameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	if(G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
		//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgSong.wav", true);
	}

	setTouchEnabled(true);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	background = CCSprite::create("mainboard.png");
	background->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	this->addChild(background, 0, 10);

	itemReplay = CCMenuItemImage::create("replay.png", "replayPr.png", this, menu_selector(MainGameScene::replayCallBack));
	itemReplay->setPosition(ccp(61.5f, 52.0f));
	this->addChild(itemReplay, 0, 11);

	itemGoMenu = CCMenuItemImage::create("menu.png", "menuPr.png", this, menu_selector(MainGameScene::menuCallBack));
	itemGoMenu->setPosition(ccp(149.5f, 52.0f));
	this->addChild(itemGoMenu, 0, 12);

	CCMenu* menu = CCMenu::create(itemGoMenu, itemReplay, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	//achievementManager = AchievementManager::create();
	effect = EffectManager::create();
	effect->InitWithTarget(this);
	
    return true;
}


void MainGameScene::initLevel(int level)
{
	//Init Effect
	lineEffectManager = CCNode::create();
	centerPointEffectManager = CCNode::create();
	shadowEffectManager = CCNode::create();
	infoCurLevelManager = CCNode::create();
	starManager = CCNode::create();

	this->addChild(shadowEffectManager, 2, TAG_SHADOW_MANAGER);
	this->addChild(lineEffectManager, 3, TAG_LINE_MANAGER);
	this->addChild(centerPointEffectManager, 4, TAG_CENTERPOINT_MANAGER);
	this->addChild(infoCurLevelManager, 5, TAG_INFO_MANAGER);
	this->addChild(starManager, 5, TAG_STAR_MANAGER);

	//Init Board Manager
	//Start at 0
	this->boardManager = new BoardManager();
	this->boardManager->init();
	this->boardManager->setLevel(level);

	this->addChild(this->boardManager, 0); //gọi trước 2 hàm dưới

	this->boardManager->initBoard();
	this->boardManager->resetBoard(false);	

	CCString* _bufLvl = CCString::createWithFormat("%d", (boardManager->curLevel + 1));

	CCString* _bufEnergy = CCString::createWithFormat("%d", boardManager->curNumMove);

	CCLabelTTF* pLabelEnergy = CCLabelTTF::create(_bufEnergy->getCString(), "Marker Felt", 80);
	pLabelEnergy->setPosition(ccp(115,340));
	pLabelEnergy->setColor(ccc3(0,0,0));
	this->addChild(pLabelEnergy,0,TAG_TEXT_ENERGY);

	CCLabelTTF* pLabelLvl = CCLabelTTF::create(_bufLvl->getCString(), "Marker Felt", 50);

	pLabelLvl->setPosition(ccp(115,495));
	pLabelLvl->setColor(ccc3(0,0,0));
	this->addChild(pLabelLvl,0,TAG_TEXT_LEVEL);	
}


void MainGameScene::menuCallBack(CCObject* pSender)
{
	this->GotoMenu();
}


void MainGameScene::replayCallBack( CCObject* pSender )
{
	this->Replay();
}


//////////////////////////////////////////////////////////////////////////
//WinDialog Call

void MainGameScene::showCompletedLevel(int lvl,int starGot)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	WinDialog* win = new WinDialog();
	win->init();
	win->InitTarget(this, lvl, starGot);
	this->addChild(win, 100, 101);
}

void MainGameScene::showFailedLevel()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	LoseDialog* lose = new LoseDialog();
	lose->init();
	lose->InitTarget(this,-1,true);
	this->addChild(lose, 100, 102);
}

void MainGameScene::GotoMenu()
{
	this->removeChildByTag(101);
	if(this->getChildByTag(102) != NULL) //lose
	{
		this->removeChildByTag(102);
	}

	CCTransitionScene* transScene = CCTransitionFade::create(0.5f, SelectLevelScene::scene());
	CCDirector::sharedDirector()->replaceScene(transScene);

	//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
}

void MainGameScene::Replay()
{
	this->removeChildByTag(101); //win
	if(this->getChildByTag(102) != NULL) //lose
	{
		this->removeChildByTag(102);
	}

	this->effect->RemoveAllEff();
	this->effect->RemoveAllEff();
	this->effect->FadeOutIn();

	this->boardManager->resetBoard(true);
	this->setTouchEnabled(true);
}

void MainGameScene::Next()
{
	this->removeChildByTag(101); //win

	int nextlevel = 1 + boardManager->curLevel;

	if(nextlevel < Map::NUMBER_OF_MAP)
	{
		//remove
		this->effect->RemoveAllEff();
		this->effect->FadeOutIn();
		this->removeChildByTag(101); //win dialog

		this->boardManager->setLevel(this->boardManager->curLevel + 1);
		this->boardManager->initBoard();
		this->boardManager->resetBoard(true);

		this->UpdateStar(0);
		this->updateTextEnergy();
		this->updateTextLevel();

		this->setTouchEnabled(true);
	}
	else
	{
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		NoMapLeftDialog* dialog = new NoMapLeftDialog();
		dialog->init();
		dialog->InitTarget(this,-1);
		this->addChild(dialog, 100, 102);
	}
}

//////////////////////////////////////////////////////////////////////////


void MainGameScene::updateTextEnergy()
{
	CCString* _bufEnergy = CCString::createWithFormat("%d", boardManager->curNumMove);

	CCLabelTTF* pLabelEnergy =	(CCLabelTTF*)this->getChildByTag(TAG_TEXT_ENERGY);
	pLabelEnergy->setString(_bufEnergy->getCString());
}

void MainGameScene::updateTextLevel()
{
	CCString* _bufLvl = CCString::createWithFormat("%d", (boardManager->curLevel + 1));

	CCLabelTTF* pLabelLvl =	(CCLabelTTF*)this->getChildByTag(TAG_TEXT_LEVEL);
	pLabelLvl->setString(_bufLvl->getCString());
}

//////////////////////////////////////////////////////////////////////////

void MainGameScene::UpdateStar( int star )
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //gốc tọa độ ở góc dưới, bên trái

	if(star >= 1)
	{
		CCSprite* s1 = CCSprite::create("star-1.png");
		s1->setPosition(ccp(41, visibleSize.height - 240));
		this->starManager->addChild(s1);

		// 		s1->setScale(0);
		// 		CCAction* ease = CCEaseElasticOut::create(
		// 			CCScaleTo::create(3, 1, 1), NULL);
		// 		s1->runAction(ease);
	}

	if(star >=2) 
	{
		CCSprite* s2 = CCSprite::create("star-2.png");
		s2->setPosition(ccp(72, visibleSize.height - 181));
		this->starManager->addChild(s2);

		// 		s2->setScale(0);
		// 		CCAction* ease = CCEaseElasticOut::create(
		// 			CCScaleTo::create(3, 1, 1), NULL);
		// 		s2->runAction(ease);
	}

	if(star>= 3)
	{
		CCSprite* s3 = CCSprite::create("star-3.png");
		s3->setPosition(ccp(141, visibleSize.height - 150));
		this->starManager->addChild(s3);

		// 		s3->setScale(0);
		// 		CCAction* ease = CCEaseElasticOut::create(
		// 			CCScaleTo::create(3, 1, 1), NULL);
		// 		s3->runAction(ease);
	}	
}

void MainGameScene::SetTouchEnable( bool istouch )
{
	this->setTouchEnabled(istouch);
}

//////////////////////////////////////////////////////////////////////////

//tanlong 

//////////////////////////////////////////////////////////////////////////

void MainGameScene::AddSTARTEff( CCPoint p )
{
	this->effect->AddStartEff(p);
// 	CCSprite* spr = CCSprite::create("effStart.png");
// 	CCAction* zoomInOut = CCRepeatForever::create(CCSequence::create(
// 		CCScaleBy::create(0.5f, 1.4f, 1.4f),
// 		CCScaleBy::create(0.5f, 1.4f, 1.4f)->reverse(),
// 		NULL));
// 
// 	spr->setPosition(p);
// 	this->addChild(spr, 99);
// 	spr->runAction(zoomInOut);
}

void MainGameScene::AddFINISHEff( CCPoint p )
{
	this->effect->AddFinishEff(p);
// 	CCSprite* spr = CCSprite::create("effFinish.png");
// 	CCActionInterval* blink = CCBlink::create(2, 2);
//	CCAction* repeat = CCRepeatForever::create(blink);

// 	spr->setPosition(p);
// 	this->addChild(spr, 99);
// 	spr->runAction(repeat
}

//////////////////////////////////////////////////////////////////////////
