#include "Player.h"
#include "input/InputTouch.h"

bool Player::init(void)
{
	if (!cocos2d::Sprite::initWithFile("img/bike1.png"))
	{
		return false;
	}
	_input = InputTouch::create();
	addChild(_input);
	this->scheduleUpdate();
	setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	setPosition(cocos2d::Vec2(0, 200));
	_speed = 3;
	return true;
}

void Player::update(float dt)
{
	if (_position.x >= cocos2d::Director::getInstance()->getVisibleSize().width)
	{
		_position.x = 0;
	}
	if (_input->IsInput())
	{
		runAction(cocos2d::JumpBy::create(0.5f, cocos2d::Vec2::ZERO, 50.f, 1));
	}
	setPosition(getPosition() + cocos2d::Vec2(_speed, 0));
	_input->update();
}
