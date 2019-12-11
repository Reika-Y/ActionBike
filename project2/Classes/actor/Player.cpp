#include "Player.h"

bool Player::init(void)
{
	if (!cocos2d::Sprite::init())
	{
		return false;
	}
	//_anim.AddAnim();
	return true;
}
