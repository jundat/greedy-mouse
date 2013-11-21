#ifndef __BOARDMANAGER_H__
#define __BOARDMANAGER_H__


#include "cocos2d.h"
#include "MapItem.h"
#include "Map.h"
#include "ItemData.h"
#include "Line.h"

#include "Global.h"

USING_NS_CC;


#define	STATUS_CHOOSE_START_ITEM	0
#define STATUS_PLAYING				1
#define	STATUS_FINISH				2


class BoardManager : public CCLayer
{
public:
	BoardManager(){}
	~BoardManager(){}
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(BoardManager);


	int status;
	int curLevel;
	int curNumMove;
	int curNumStar;
	MapItem *lastItemSelected;
	MapItem *curItemSelected;

	void setLevel(int level);
	void initBoard();
	void resetBoard(bool isReplay);
	bool isTouchedItemPossible(MapItem *item);
	CCArray* getLockWithKeyID(int key);
	MapItem* getItemAtPos(int row,int col);

	bool isLimitStep(int row,int col);

	void addNewLineEffect(CCPoint pos1,CCPoint pos2);
	void addNewShadowEffect(CCPoint pos);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	virtual void onEnter();
	virtual void onExit();

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();
};

#endif //__BOARDMANAGER_H__