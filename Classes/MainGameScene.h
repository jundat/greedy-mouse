#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"
#include "BoardManager.h"
#include "Achievement.h"
#include "AchievementManager.h"
#define COCOS2D_DEBUG 1

USING_NS_CC;
#include "Global.h"

#include "EffectManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;



class MainGameScene : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene(int level);
	CREATE_FUNC(MainGameScene);


	CCSprite *background;
	CCNode *lineEffectManager;
	CCNode *centerPointEffectManager;
	CCNode *shadowEffectManager;
	CCNode *infoCurLevelManager;
	CCNode *starManager;
	//AchievementManager *achievementManager;
	
	BoardManager *boardManager;

	//button
	CCMenuItemImage *itemReplay;
	CCMenuItemImage *itemGoMenu;

	EffectManager* effect;

	//level count from 1
	void initLevel(int level);
    
    void menuCallBack(CCObject* pSender);
	void replayCallBack(CCObject* pSender);

	void showCompletedLevel(int lvl,int starGot);
	void showFailedLevel();
	void updateTextEnergy();
	void updateTextLevel();

	////////////////// WinDialog call
	void GotoMenu();
	void Replay();
	void Next();
	////////////////// tan long


	//////////////////////////////////////////////////////////////////////////
	void UpdateStar(int star);
	//////////////////////////////////////////////////////////////////////////
	void AddSTARTEff(CCPoint p);
	void AddFINISHEff(CCPoint p);
	//////////////////////////////////////////////////////////////////////////

	void SetTouchEnable(bool istouch);
};

#endif // __MAIN_GAME_SCENE_H__
