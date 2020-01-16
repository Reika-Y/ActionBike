#include "InputCheck.h"
#include "../ActionControl.h"
#include "../input/InputBase.h"

bool InputCheck::operator()(cocos2d::Sprite& sp, ActModule& act)
{
	if (act._input->IsInput())
	{
		return true;
	}
	return false;
}
