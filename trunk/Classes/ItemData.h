#ifndef __ITEM_DATA_H__
#define __ITEM_DATA_H__


class ItemData
{
public :
	int id;
	int col;
	int row;
	int energy;
	int destCol;
	int destRow;
	int keyId;
	int lockId;
	int lockItemId;

public:
	ItemData()
	{
		id=0;
		col=-1;
		row=-1;
		energy=-1;
		destCol=-1;
		destRow=-1;
		keyId=-1;
		lockId=-1;
		lockItemId = 0;
	}

	ItemData(int _id, int _col, int _row, int _energy, int _destCol, int _destRow, int _keyId, int _lockId,int _lockItemId)
	{
		id=_id;
		col=_col;
		row=_row;
		energy=_energy;
		destCol=_destCol;
		destRow=_destRow;
		keyId=_keyId;
		lockId=_lockId;
		lockItemId = _lockItemId;
	}
};


#endif //__ITEM_DATA_H__