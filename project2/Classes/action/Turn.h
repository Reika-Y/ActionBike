#pragma once
#include <cocos2d.h>
#include "ActionControl.h"

// 画像反転
struct Turn
{
	bool operator()(cocos2d::Sprite& sp, ActModule& act, float& dt);
};