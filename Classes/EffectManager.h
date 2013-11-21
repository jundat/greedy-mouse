#ifndef __EFFECT_MNG_H__
#define __EFFECT_MNG_H__

#include "cocos2d.h"
USING_NS_CC;
#include <vector>
using namespace std;


class EffectManager : public cocos2d::CCLayerColor
{
public:
	EffectManager(){}
	~EffectManager(){}

    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(EffectManager);
    
	CCLayer* parentLayer;
	void InitWithTarget(CCLayer* parentLayer);

	void FadeOutIn();

	//START, FINISH
	vector<CCSprite*> listStartSpr;
	vector<CCSprite*> listFinishSpr;

	void AddStartEff(CCPoint p);
	void AddFinishEff(CCPoint p);

	void RemoveAllStartEff();
	void RemoveAllFinishEff();

	void RemoveAllEff();
};

#endif // __EFFECT_MNG_H__
