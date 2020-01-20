#include "Move.h"

float m_speed = 120.0f;

bool Move::operator()(cocos2d::Sprite& sp, ActModule& act,float& dt)
{
	sp.setPositionX(sp.getPositionX() + m_speed * dt);
	return true;
}
