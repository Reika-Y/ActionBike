#pragma once
#include <cocos2d.h>
#include "../ActionControl.h"


struct InputCheck
{
	bool operator()(cocos2d::Sprite& sp, ActModule& act, float& dt);
};

