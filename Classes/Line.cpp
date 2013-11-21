#include "Line.h"

#define SIZELINE 8
Line::Line(void)
{
}


Line::~Line(void)
{
	
}


Line* Line::createLine(CCPoint _startPoint,CCPoint _endPoint)
{
	Line * sprite = new Line();
	if(sprite && sprite->initWithFile("LinePoint.png"))
	{
		CCPoint edge = _endPoint - _startPoint;
		float temp = atan2(edge.x,edge.y);
		float angle = temp / 3.14 * 180;
		float length = edge.getLength();

		sprite->setScaleY(length / SIZELINE);
		sprite->setScaleX(2);

		sprite->setPosition(_startPoint + edge/2);
		sprite->setRotation(angle);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}