#pragma once

class cocos2d::Sprite;
struct ActModule;

struct Jumping
{
	bool operator()(cocos2d::Sprite& sp, ActModule& act,float& dt);
};