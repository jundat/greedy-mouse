#include "MapItem.h"
#include <string>
using namespace std;

bool MapItem::init()
{
	if( CCSprite::init() == false)
	{
		return false;
	}

	m_id = -1;
	m_Col = -1;
	m_Row = -1;
	m_energy = -1;
	m_destCol = -1;
	m_destRow = -1;
	m_keyId = -1;
	m_lockId = -1;
	itemInvi = NULL;
	isInviItemActived = false;
	m_curStatus = sNormal;
	isAvailable = true;

	return true;
}

MapItem::MapItem(void)
{
	
}

MapItem::~MapItem(void)
{
}

MapItem* MapItem::createItem(int _id, int _col, int _row, int _energy, int _destCol, int _destRow, int _keyId, int _lockId,int _lockItemId)
{
	CCLOG("[info] Start CreateItem1!");
	string spriteName;
	MapItem* mapItem = MapItem::create();
	
	switch (_id)
	{
	case 0:
		break;
	case 1:
		spriteName = string("1.png");
		break;
	case 2:
		spriteName = string("2.png");
		break;
	case 3:
		spriteName = string("3.png");
		break;
	case 4:
		spriteName = string("4.png");
		break;
	case 5:
		{
			if(_energy == 10)
			{
				spriteName = string("5-1.png");
			}
			else
			if(_energy == 5)
			{
				spriteName = string("5-2.png");
			}
			else
			{
				spriteName = string("5-3.png");
			}
		}
		
		break;
	case 6:
		spriteName = string("bridge.png");
		break;
	case 7:
		switch (_lockId)
		{
		case 1:
			spriteName = string("lock1.png");
			break;
		case 2:
			spriteName = string("lock2.png");
			break;
		case 3:
			spriteName = string("lock3.png");
			break;
		case 4:
			spriteName = string("lock4.png");
			break;
		}

		break;
	case 8:
		switch (_keyId)
		{
		case 1:
			spriteName = string("key1.png");
			break;
		case 2:
			spriteName = string("key2.png");
			break;
		case 3:
			spriteName = string("key3.png");
			break;
		case 4:
			spriteName = string("key4.png");
			break;
		}

		break;
	case 9:
		spriteName = string("9.png");
		break;
	default:
		break;
	}

	CCLOG("[info] SpriteName1: %s", spriteName.c_str());
	CCLOG("initWithFile");

	if(mapItem && mapItem->initWithFile(spriteName.c_str()))
	{	
		CCLOG("initWithFile OK!");

		mapItem->m_id = _id;
		mapItem->setCol(_col);
		mapItem->setRow(_row);
		mapItem->setEnergy(_energy);
		mapItem->m_destRow = _destRow;
		mapItem->m_destCol = _destCol;
		mapItem->setKeyId(_keyId);
		mapItem->setLockId(_lockId);
		mapItem->setPosition(ccp(DELTA_MAP_X + SIZE_CELL * _col + (SIZE_CELL / 2), DELTA_MAP_Y + SIZE_CELL * _row + (SIZE_CELL / 2)));
		mapItem->setCurStatus(sNormal);
		mapItem->setLockItemId(_lockItemId);
		mapItem->setIsIAvailable(true);

		if(mapItem->getDestRow() != -1 && mapItem->getDestCol() != -1)
		{
			int dir = mapItem->getDirBridge();

			switch (dir)
			{
			case UP:
				mapItem->setRotation(-90.0f);
				break;
			case DOWN:
				mapItem->setRotation(90.0f);
				break;
			case LEFT:
				mapItem->setRotation(-180.0f);
				break;
			case RIGHT:
				break;
			case LEFT_UP:
				mapItem->setRotation(225.0f);
				break;
			case LEFT_DOWN:
				mapItem->setRotation(-225.0f);
				break;
			case RIGHT_DOWN:
				mapItem->setRotation(-45.0f);
				break;
			case RIGHT_UP:
				mapItem->setRotation(45.0f);
				break;
			}
		}
		
		return mapItem;
	}
	
	CCLOG("[info] End CreateItem1");

	return NULL;
}

MapItem* MapItem::createItem(bool _isAvaible,int _id, int _col, int _row, int _energy, int _destCol, int _destRow, int _keyId, int _lockId, int _lockItemId)
{
	MapItem* item = createItem( _id,  _col,  _row,  _energy,  _destCol,  _destRow,  _keyId,  _lockId,  _lockItemId);
	if(item != NULL)
	{
		item->isAvailable = _isAvaible;
	}

	return item;
}

void MapItem::makeItemActive()
{
	if(m_curStatus == sNormal)
	{
		m_curStatus = sActived;
		
	}
}

int MapItem::getIDForIt()
{
	return this->m_id;
}

int MapItem::getDirBridge()
{
	if(m_Col == m_destCol)
	{
		if (m_Row < m_destRow)
			return UP;
		else
		{
			return DOWN;
		}
	}

	if(m_Row == m_destRow)
	{
		if(m_Col < m_destCol)
			return RIGHT;
		else
		{
			return LEFT;
		}
	}
	
	if(m_Row > m_destRow && m_Col < m_destCol )
		return RIGHT_UP;

	if(m_Row > m_destRow && m_Col > m_destCol)
	{
		CCLog("LEFT DOWN : Pos : %d - %d||||| Pos Des: %d - %d :",m_Row,m_Col,m_destRow,m_destCol);
		return LEFT_DOWN;
	}

	if(m_Row < m_destRow && m_Col > m_destCol)
	{
		CCLog("LEFT UP :  Pos : %d - %d||||| Pos Des: %d - %d :",m_Row,m_Col,m_destRow,m_destCol);
		return LEFT_UP;
	}

	if(m_Row < m_destRow && m_Col < m_destCol)
		return RIGHT_DOWN;
}

void MapItem::createInviItem()
{
	//Create item invi
	if(m_lockItemId != 0)
	{
		CCLog("LOCK ITEM ID : %d", m_lockItemId);

		this->itemInvi = MapItem::createItem(false,m_lockItemId,m_Col,m_Row,m_energy,m_destCol,m_destRow,-1,-1,0);
		if(this->itemInvi != NULL)
			this->getParent()->addChild(itemInvi,(this->getZOrder() - 0.1f),99);
	}
}



 