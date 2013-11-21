#ifndef __CAMPAIGN_SCENE_H__
#define __CAMPAIGN_SCENE_H__

#include "cocos2d.h"

USING_NS_CC; //đừng bao giờ quên cái nồi này


#include "Global.h"


class CampaignScene : public cocos2d::CCLayerColor
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	CCSprite* loadMap(CCSprite* sprCampaign);

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void back2Menu(CCObject* pSender);
	void gotoplay(int level);

	//touch...

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	// implement the "static node()" method manually
	CREATE_FUNC(CampaignScene);

public:
	static float s_data[][2];


private:
	bool isMove;

	CCSprite* m_sprCampaign;
	CCSprite* m_sprPointBorder; //current point
	CCSprite* m_sprDialogPoint;
	CCSprite* m_sprDialogLine;
	CCLabelBMFont* m_labelBoxTitle;
	CCLabelBMFont* m_labelBoxContent;
	CCLabelBMFont* m_lableBold;
	CCLabelBMFont* m_lableStar;
	CCSprite* m_sprBold;
	CCSprite* m_sprStar;


	CCSprite* m_sprBlend;
	CCSprite* m_sprBlendCopy;

	float m_scale;
	CCMenuItemImage* m_itemZoomIn;
	CCMenuItemImage* m_itemZoomOut;

	CCAnimation* m_animPlay;
};

#endif // __HELLOWORLD_SCENE_H__
