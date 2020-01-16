#pragma once
#include <cocos2d.h>
#include "../ActionControl.h"

struct Idle
{
	bool operator()(cocos2d::Sprite& sp, ActModule& act);
};