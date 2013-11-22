#ifndef __NO_MAP_LEFT_DIALOG_H__
#define __NO_MAP_LEFT_DIALOG_H__

#include "cocos2d.h"
#include "MainGameScene.h"

#include "Global.h"


class NoMapLeftDialog : public cocos2d::CCLayerColor
{
public:
	NoMapLeftDialog(){}
	~NoMapLeftDialog(){}
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(NoMapLeftDialog);

	CCSprite* mainSpr;

	MainGameScene* mainGameScene;
	int currentLevel;

	void InitTarget(MainGameScene* maingamescene, int level);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	// a selector callback
	void GotoMenu(CCObject* sender);
	void Replay(CCObject* sender);
};

#endif // __NO_MAP_LEFT_DIALOG_H__
