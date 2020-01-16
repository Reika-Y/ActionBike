#pragma once

class Sprite;
struct ActModule;

struct Fall
{
	bool operator()(cocos2d::Sprite& sp, ActModule& act);
};
