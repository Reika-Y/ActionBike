#pragma once
#include <cocos2d.h>
#include "input/InputBase.h"

class Actor:public cocos2d::Sprite
{
public:
private:
protected:
	int _speed;
	InputBase* _input = nullptr;
};

