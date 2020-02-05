#include "Player.h"
#include "../input/InputTouch.h"
#include "../action/ActionDefinition.h"
#include "../scene/GameScene.h"
#include "../item/Item.h"
#include "../info/ScoreInfo.h"

bool Player::init(void)
{
	_rect = cocos2d::Rect(0, 0, 64, 64);
	//auto sp = cocos2d::Sprite::create();
	//sp->setTextureRect(_rect);
	//sp->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	//addChild(sp);
	if (!cocos2d::Sprite::initWithFile("img/bike1.png"))
	{
		return false;
	}
	_input = InputTouch::create();
	addChild(_input);
	//this->scheduleUpdate();
	setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);

	_isDie = false;

	addModule();

	return true;
}

void Player::update(float dt)
{
	getBoundingBox();
	SetCornerPoint(_rect);
	// 状態更新
	_act.Update(*this, dt);

	// アイテムとの接触判定
	auto stage = dynamic_cast<GameScene*>(cocos2d::Director::getInstance()->getRunningScene())->getstage();
	for (auto rect : stage->getItemList())
	{
		if (getBoundingBox().intersectsRect(rect->getBoundingBox()))
		{
			if (!rect->IsErace())
			{
				ScoreInfo::getInstance()->AddScore(rect->Score());
				rect->IsErace(true);
			}
		}
	}

	_input->update();
}

void Player::addModule(void)
{
	{
		// アイドル
		ActModule idle;
		idle._actID = ACT_ID::IDLE;
		idle.white.emplace_back(ACT_ID::JUMP);
		idle._runAct = Idle();
		_act.AddModeule(idle);	
	}
	{
		// 走る
		ActModule run;
		run._actID = ACT_ID::RUN;
		run.white.emplace_back(ACT_ID::JUMP);
		run.white.emplace_back(ACT_ID::FALL);
		run._actFuncList.emplace_back(CollisionCheck());
		//run._actFuncList.emplace_back(OnGround());
		run._runAct = Move();
		run._col.emplace_back(static_cast<int>(CORNER_POINT::RT));
		run._col.emplace_back(static_cast<int>(CORNER_POINT::RD));
		_act.AddModeule(run);
	}
	{
		// ジャンプした瞬間
		ActModule jump;
		jump._actID = ACT_ID::JUMP;
		jump.black.emplace_back(ACT_ID::JUMP);
		jump.white.emplace_back(ACT_ID::JUMPING);
		jump._input = _input;
		jump._actFuncList.emplace_back(ModuleCheck());
		jump._actFuncList.emplace_back(InputCheck());
		jump._actFuncList.emplace_back(CollisionCheck());
		jump._runAct = Jump();
		_act.AddModeule(jump);
	}
	{
		// ジャンプ中
		ActModule jumping;
		jumping._actID = ACT_ID::JUMPING;
		jumping.black.emplace_back(ACT_ID::FALL);
		//jumping.white.emplace_back(ACT_ID::RUN);
		jumping.white.emplace_back(ACT_ID::JUMPING);
		jumping._actFuncList.emplace_back(ModuleCheck());
		jumping._actFuncList.emplace_back(CollisionCheck());
		jumping._col.emplace_back(static_cast<int>(CORNER_POINT::TL));
		jumping._col.emplace_back(static_cast<int>(CORNER_POINT::TR));
		jumping._runAct = Jumping();
		_act.AddModeule(jumping);
	}
	{
		// 落下
		ActModule fall;
		fall.white.emplace_back(ACT_ID::FALL);
		fall._actID = ACT_ID::FALL;
		fall._actFuncList.emplace_back(ModuleCheck());
		fall._actFuncList.emplace_back(CollisionCheck());
		fall._col.emplace_back(static_cast<int>(CORNER_POINT::BL));
		fall._col.emplace_back(static_cast<int>(CORNER_POINT::BR));
		fall._runAct = Fall();
		_act.AddModeule(fall);
	}
}

void Player::addAnim(void)
{
}
