#include "Jump.h"
#include "../actor/Actor.h"

bool Jump::operator()(cocos2d::Sprite& sp, ActModule& act)
{
	if (dynamic_cast<Actor*>(&sp)->isJumping())
	{
		return false;
	}
	dynamic_cast<Actor*>(&sp)->isJumping(true);
	// ジャンプ終了後に行う
	auto callback = cocos2d::CallFuncN::create([&sp](cocos2d::Ref * sender)
	{
		dynamic_cast<Actor*>(&sp)->isJumping(false);
	});
	auto action = cocos2d::Sequence::create(cocos2d::JumpTo::create(1.0f, sp.getPosition(), 100, 1), callback, nullptr);
	sp.runAction(action);
	return true;
}
