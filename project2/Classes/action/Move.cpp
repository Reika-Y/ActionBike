#include "Move.h"

bool Move::operator()(cocos2d::Sprite& sp, ActModule& act)
{
	sp.setPositionX(sp.getPositionX() + 3);
	return true;
}
