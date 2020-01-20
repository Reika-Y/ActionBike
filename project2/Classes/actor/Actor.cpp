#include "Actor.h"

Actor::Actor()
{
}

InputBase* Actor::getInput(void)
{
	return _input;
}

ActionControl& Actor::GetActionCtr(void)
{
	return _act;
}

const CornerPoints& Actor::GetCornerPoints(void) const
{
	return _corner;
}

bool Actor::isDie(void)
{
	return _isDie;
}

void Actor::isDie(bool flag)
{
	_isDie = flag;
}

bool Actor::isJumping(void)
{
	return _isJumping;
}

void Actor::isJumping(bool flag)
{
	_isJumping = flag;
}

float Actor::accel(void)
{
	return _accel;
}

void Actor::accel(float num)
{
	_accel = num;
}

void Actor::SetCornerPoint(cocos2d::Rect rect)
{
	_corner[static_cast<int>(CORNER_POINT::LD)] = rect.origin + _position + cocos2d::Vec2(-1, 1);
	_corner[static_cast<int>(CORNER_POINT::LT)] = rect.origin + _position + cocos2d::Vec2(-1, rect.size.height - 1);
	_corner[static_cast<int>(CORNER_POINT::RD)] = rect.origin + _position + cocos2d::Vec2(rect.size.width + 1, 1);
	_corner[static_cast<int>(CORNER_POINT::RT)] = rect.origin + _position + cocos2d::Vec2(rect.size.width + 1, rect.size.height - 1);
	_corner[static_cast<int>(CORNER_POINT::TL)] = rect.origin + _position + cocos2d::Vec2(1, rect.size.height + 1);
	_corner[static_cast<int>(CORNER_POINT::TR)] = rect.origin + _position + cocos2d::Vec2(rect.size.width - 1, rect.size.height + 1);
	_corner[static_cast<int>(CORNER_POINT::BL)] = rect.origin + _position + cocos2d::Vec2(1, -1);
	_corner[static_cast<int>(CORNER_POINT::BR)] = rect.origin + _position + cocos2d::Vec2(rect.size.width - 1, -1);
}
