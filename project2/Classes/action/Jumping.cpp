#include <cocos2d.h>
#include "Jumping.h"
#include "../actor/Actor.h"

bool Jumping::operator()(cocos2d::Sprite& sp, ActModule& act,float& dt)
{
	if (!dynamic_cast<Actor*>(&sp)->isJumping())
	{
		return false;
	}
	dynamic_cast<Actor*>(&sp)->accel(dynamic_cast<Actor*>(&sp)->accel() - gravity * dt);
	if (dynamic_cast<Actor*>(&sp)->accel() <= 0)
	{
		dynamic_cast<Actor*>(&sp)->isJumping(false);
		return false;
	}
	sp.setPositionY(sp.getPositionY() + dynamic_cast<Actor*>(&sp)->accel());
	return true;
}
