#ifndef __WINDIALOG_H__
#define __WINDIALOG_H__

#include "cocos2d.h"
#include "MainGameScene.h"
USING_NS_CC;

#include "Global.h"


class WinDialog : public cocos2d::CCLayerColor
{
public:
	WinDialog(){}
	~WinDialog(){}
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(WinDialog);

	CCSprite* mainSpr;

	MainGameScene* mainGameScene;
	int currentLevel;
	int star;

	void InitTarget(MainGameScene* maingamescene, int level, int star);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	// a selector callback
	void GotoMenu(CCObject* sender);
	void Replay(CCObject* sender);
	void Next(CCObject* sender);
};

#endif // __WIN_DIALOG_SCENE_H__
