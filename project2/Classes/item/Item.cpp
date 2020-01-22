#include "Item.h"

bool Item::init(cocos2d::Texture2D* t)
{
	if (!Sprite::initWithTexture(t))
	{
		return false;
	}

	_score = 10;
	_isErace = false;

	return true;
}

const int Item::Score(void)
{
	return _score;
}

bool Item::IsErace(void)
{
	return _isErace;
}

void Item::IsErace(bool flag)
{
	_isErace = flag;
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
