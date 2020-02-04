#pragma once
#include <cocos2d.h>

struct ActModule;

struct Jumping
{
	bool operator()(cocos2d::Sprite& sp, ActModule& act,float& dt);
};