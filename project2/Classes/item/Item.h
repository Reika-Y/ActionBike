#pragma once
#include <cocos2d.h>

class Item:public cocos2d::Sprite
{
public:
	static Item* create(cocos2d::Texture2D* t);
	bool init(cocos2d::Texture2D* t);
	const int GetScore(void);
private:
	int _score;
};

