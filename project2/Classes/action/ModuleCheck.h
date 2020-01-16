#pragma once
#include <cocos2d.h>
#include "../ActionControl.h"

struct ModuleCheck
{
	bool operator()(cocos2d::Sprite& sp, ActModule& act);
};