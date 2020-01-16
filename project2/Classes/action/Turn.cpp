#include "Turn.h"

bool Turn::operator()(cocos2d::Sprite& sp, ActModule& act)
{
	sp.runAction(cocos2d::FlipX::create(true));
	return true;
}
