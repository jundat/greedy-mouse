#ifndef __ACHIEVEMENT_SCENE_H__
#define __ACHIEVEMENT_SCENE_H__

#include "cocos2d.h"
USING_NS_CC; //đừng bao giờ quên cái nồi này

#include "Global.h"


#include <vector>
using namespace std;

class AchievementScene : public cocos2d::CCLayerColor
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene(vector<int> listAchi);

	vector<int> listAchi;
	void InitAchievement(vector<int> listAchi);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	// implement the "static node()" method manually
	CREATE_FUNC(AchievementScene);
};

#endif // __ACHIEVEMENT_SCENE_H__
