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

private:
	CCSprite* mainSprite;
};
#endif