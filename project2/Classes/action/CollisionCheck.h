#pragma once

class Sprite;
struct ActModule;

struct CollisionCheck
{
	bool operator()(cocos2d::Sprite& sp, ActModule& act);
};
