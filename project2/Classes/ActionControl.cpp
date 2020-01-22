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
	auto check = [](cocos2d::Sprite& sp, ActModule& act,float& dt) {
		for (auto actFunc : act._actFuncList)
		{
			if (!actFunc(sp, act,dt))
			{
				return false;
			}
		}
		return true;
	};

	// 切り替え
	bool flag = false;
	for (auto act:actModeule)
	{
		// アイドルは何もしない
		if (act.first == ACT_ID::IDLE)
		{
			continue;
		}


		if (check(sp, act.second,dt))
		{
			act.second._runAct(sp, act.second,dt);
			if (_oldId != ACT_ID::JUMPING)
			{
				_oldId = act.first;
			}
			flag = true;

			// ジャンプが終了したときの処理
			if (_oldId == ACT_ID::JUMPING && !dynamic_cast<Actor&>(sp).isJumping())
			{
				actModeule[ACT_ID::FALL]._runAct(sp, actModeule[ACT_ID::FALL], dt);
				_oldId = ACT_ID::FALL;
			}
		}
		else if (_oldId == ACT_ID::JUMPING && act.second._actID == ACT_ID::JUMPING)
		{
			// ジャンプ中に頭が当たった時
			dynamic_cast<Actor*>(&sp)->isJumping(false);
			actModeule[ACT_ID::FALL]._runAct(sp, actModeule[ACT_ID::FALL], dt);
			_oldId = ACT_ID::FALL;
		}
	}
	if (!flag)
	{
		_oldId = ACT_ID::IDLE;
		actModeule[ACT_ID::IDLE]._runAct(sp, actModeule[ACT_ID::IDLE], dt);
	}
}

ActModule ActionControl::GetOldModule(void)
{
	return actModeule[_oldId];
}

void ActionControl::SetNextAct(ACT_ID id)
{
	_nextId = id;
}

