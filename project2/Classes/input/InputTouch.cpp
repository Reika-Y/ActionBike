#include "InputTouch.h"

bool InputTouch::IsInput()
{
	return _state[TRIGGER::NOW]._isFlag && (!_state[TRIGGER::OLD]._isFlag);
}

bool InputTouch::IsPressing()
{
	return _state[TRIGGER::OLD]._isFlag && _state[TRIGGER::NOW]._isFlag;
}

bool InputTouch::IsNotInput()
{
	return !(_state[TRIGGER::OLD]._isFlag && _state[TRIGGER::NOW]._isFlag);
}

void InputTouch::update(void)
{
	_state[TRIGGER::OLD]._isFlag = _state[TRIGGER::NOW]._isFlag;
}

InputTouch::InputTouch()
{
	InputInfo info;
	info._isFlag = false;
	info._position = cocos2d::Vec2::ZERO;
	_state.emplace(TRIGGER::OLD, info);
	_state.emplace(TRIGGER::NOW, info);
}

InputTouch::~InputTouch()
{
}

bool InputTouch::init()
{
	auto swipe = cocos2d::EventListenerTouchOneByOne::create();
	swipe->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		_state[TRIGGER::OLD]._position = touch->getLocation();
		_state[TRIGGER::NOW]._position = touch->getLocation();
		_state[TRIGGER::NOW]._isFlag = true;
		return true;
	};

	swipe->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		_state[TRIGGER::NOW]._position = touch->getLocation();
		_state[TRIGGER::NOW]._isFlag = true;
		return true;
	};

	// 指が画面に触れてないとき
	swipe->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		_state[TRIGGER::OLD]._position = cocos2d::Vec2::ZERO;
		_state[TRIGGER::OLD]._isFlag = false;
		_state[TRIGGER::NOW]._position = cocos2d::Vec2::ZERO;
		_state[TRIGGER::NOW]._isFlag = false;
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(swipe, this);
	return true;
}
