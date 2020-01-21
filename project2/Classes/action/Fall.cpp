#include <cocos2d.h>
#include "Fall.h"
#include "../actor/Actor.h"

bool Fall::operator()(cocos2d::Sprite& sp, ActModule& act,float& dt)
{
	dynamic_cast<Actor&>(sp).accel(dynamic_cast<Actor&>(sp).accel() + gravity * dt);
	sp.setPositionY(sp.getPositionY() - dynamic_cast<Actor&>(sp).accel());
	return true;
}
