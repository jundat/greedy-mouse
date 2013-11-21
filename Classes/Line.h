#ifndef __LINE_H__
#define __LINE_H__
#include "cocos2d.h"
USING_NS_CC;

class Line  : public CCSprite
{
public:
	Line(void);
	~Line(void);

	static Line* createLine(CCPoint _startPoint,CCPoint _endPoint);
};

#endif // __LINE_H__