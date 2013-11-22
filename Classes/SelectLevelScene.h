#ifndef _SELECT_LEVEL_SENCE_H_
#define _SELECT_LEVEL_SENCE_H_

#include "cocos2d.h"
USING_NS_CC;

class SelectLevelScene : public cocos2d::CCLayerColor
{
public:
	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(SelectLevelScene);

	bool isMoved;
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void GotoPlay( int level );

private:
	CCSprite* mainSprite;
};
#endif