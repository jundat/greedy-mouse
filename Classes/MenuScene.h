#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC; //đừng bao giờ quên cái nồi này

#include "Global.h"


class MenuScene : public cocos2d::CCLayerColor
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	void playClicked(CCObject* pSender);
	void tutorialClicked(CCObject* pSender);
	void aboutClicked(CCObject* pSender);
	void achievementClicked(CCObject* pSender);
	void soundClicked(CCObject* pSender);
	void initAnimation();

	CCSprite* headerMenu;

	CCMenuItemImage* start;
	CCMenuItemImage* tutorial;

	CCMenuItemImage* about;
	CCMenuItemImage* achievement;

	CCMenuItemToggle* sound;



	// implement the "static node()" method manually
	CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
