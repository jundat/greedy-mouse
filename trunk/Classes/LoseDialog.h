#ifndef __LOSEDIALOG_H__
#define __LOSEDIALOG_H__

#include "cocos2d.h"
#include "MainGameScene.h"

#include "Global.h"


class LoseDialog : public cocos2d::CCLayerColor
{
public:
	LoseDialog(){}
	~LoseDialog(){}
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(LoseDialog);

	CCSprite* mainSpr;

	MainGameScene* mainGameScene;
	int currentLevel;

	void InitTarget(MainGameScene* maingamescene, int level, bool isNoMoveLeft);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	// a selector callback
	void GotoMenu(CCObject* sender);
	void Replay(CCObject* sender);
	void Next(CCObject* sender);
};

#endif // __LOSEDIALOG_SCENE_H__
