#include "Jump.h"
#include "../actor/Actor.h"

bool Jump::operator()(cocos2d::Sprite& sp, ActModule& act,float& dt)
{
	if (dynamic_cast<Actor*>(&sp)->isJumping())
	{
		return false;
	}
	dynamic_cast<Actor*>(&sp)->isJumping(true);
	dynamic_cast<Actor*>(&sp)->accel(7);

	return true;
}
