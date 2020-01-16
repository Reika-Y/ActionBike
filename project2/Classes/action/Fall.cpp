#include <cocos2d.h>
#include "Fall.h"

bool Fall::operator()(cocos2d::Sprite& sp, ActModule& act)
{
	sp.setPositionY(sp.getPositionY() - 3);
	return true;
}
