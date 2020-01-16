#include "ModuleCheck.h"
#include "../Actor/Actor.h"

bool ModuleCheck::operator()(cocos2d::Sprite& sp, ActModule& act)
{
	auto oldModule = dynamic_cast<Actor*>(&sp)->GetActionCtr().GetOldModule();

	for (auto b : oldModule.black)
	{
		if (b == act._actID)
		{
			return false;
		}
	}
	for (auto w : oldModule.white)
	{
		if (w == act._actID)
		{
			return true;
		}
	}
	return false;
}
