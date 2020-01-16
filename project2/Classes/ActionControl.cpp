#include "ActionControl.h"
#include "action/ActionDefinition.h"
#include "actor/Player.h"

ActionControl::ActionControl()
{
	actModeule.clear();
	_oldId = ACT_ID::IDLE;
	_nextId = ACT_ID::IDLE;
}

ActionControl::~ActionControl()
{
}

void ActionControl::AddModeule(ActModule& act)
{
	actModeule.emplace(act._actID, act);
}

void ActionControl::Update(cocos2d::Sprite& sp,float dt)
{
	auto check = [](cocos2d::Sprite& sp, ActModule& act) {
		for (auto actFunc : act._actFuncList)
		{
			if (!actFunc(sp, act))
			{
				return false;
			}
		}
		return true;
	};

	// 切り替え
	ACT_ID id = ACT_ID::RUN;

	auto input = dynamic_cast<InputBase*>(dynamic_cast<Player&>(sp).getInput());
	if (input->IsInput())
	{
		id = ACT_ID::JUMP;
	}

	if (dynamic_cast<Actor*>(&sp)->isJumping())
	{
		_oldId = ACT_ID::JUMP;
	}

	if (check(sp, actModeule[id]))
	{
		actModeule[id]._runAct(sp, actModeule[id]);
		if (check(sp, actModeule[ACT_ID::FALL]) && _oldId != ACT_ID::JUMP)
		{
			actModeule[ACT_ID::FALL]._runAct(sp, actModeule[ACT_ID::FALL]);
		}
	}
	else
	{
		id = ACT_ID::IDLE;
		actModeule[ACT_ID::IDLE]._runAct(sp, actModeule[ACT_ID::IDLE]);
	}
	_oldId = id;
}

ActModule ActionControl::GetOldModule(void)
{
	return actModeule[_oldId];
}

void ActionControl::SetNextAct(ACT_ID id)
{
	_nextId = id;
}

