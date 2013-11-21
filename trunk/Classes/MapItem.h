#ifndef __MAPITEM_H__
#define __MAPITEM_H__
#include "cocos2d.h"
#include "ConstantValues.h"
USING_NS_CC;


//IdItem
#define	None 0
#define Start 1
#define	Finish 2
#define	Normal 3
#define	Star 4
#define Energy 5
#define Bridge 6
#define	Lock 7
#define	Key 8
#define	Teleport 9

//KeyLockId
#define	KNone -1
#define Red  2
#define Green  4
#define Blue  1
#define Yellow  3

//DirBridge
#define 	UP 1
#define 	DOWN  2
#define 	LEFT  3
#define 	RIGHT  4
#define 	LEFT_UP  5
#define 	LEFT_DOWN  6
#define 	RIGHT_DOWN   7
#define 	RIGHT_UP  8

//StatusId
#define 	sNormal 0
#define 	sActived  1
#define 	sDeactive  2

class MapItem : public CCSprite
{
public:
	CC_SYNTHESIZE(int, m_id, Id);
	CC_SYNTHESIZE(int, m_Col, Col);
	CC_SYNTHESIZE(int, m_Row, Row);
	CC_SYNTHESIZE(int, m_energy, Energy);
	CC_SYNTHESIZE(int, m_destCol, DestCol);
	CC_SYNTHESIZE(int, m_destRow, DestRow);
	CC_SYNTHESIZE(int, m_keyId, KeyId);
	CC_SYNTHESIZE(int, m_lockId, LockId);
	CC_SYNTHESIZE(int, m_curStatus, CurStatus);
	CC_SYNTHESIZE(int, m_lockItemId, LockItemId);
	CC_SYNTHESIZE(MapItem *, itemInvi, ItemInvi);
	CC_SYNTHESIZE(bool, isInviItemActived, IsInviItemActived);
	CC_SYNTHESIZE(bool, isAvailable, IsIAvailable);

	MapItem(void);
	~MapItem(void);

	virtual bool init(void);
	CREATE_FUNC(MapItem);

	static MapItem* createItem(int _id, int _col, int _row, int _energy, int _destCol, int _destRow, int _keyId, int _lockId,int _lockItemId);
	static MapItem* createItem(bool _isAvailable,int _id, int _col, int _row, int _energy, int _destCol, int _destRow, int _keyId, int _lockId,int _lockItemId);
	CCRect rect();
	bool containsTouchLocation(CCTouch* touch);

	void makeItemActive();
	void createInviItem();

	int getIDForIt();
	int getRowForIt()
	{
		return m_Row;
	}
	int getColForIt()
	{
		return m_Col;
	}
	int getDesRowForIt()
	{
		return m_destRow;
	}

	int getDesColForIt()
	{
		return m_destCol;
	}

	bool getIsIAvailableForIt()
	{
		return isAvailable;
	}

	int getDirBridge();

};

#endif // __MAPITEM_H__