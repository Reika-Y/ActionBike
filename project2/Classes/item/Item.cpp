#include "Item.h"

bool Item::init(cocos2d::Texture2D* t)
{
	if (!Sprite::initWithTexture(t))
	{
		return false;
	}

	_score = 0;

	return true;
}

const int Item::GetScore(void)
{
	return _score;
}

Item* Item::create(cocos2d::Texture2D* t)
{
	Item* p = new Item();

	if (p && p->init(t))
	{
		p->autorelease();
		return p;
	}
	else
	{
		delete p;
		p = nullptr;
	}
	return nullptr;
}
