#include "ScoreInfo.h"

ScoreInfo* ScoreInfo::getInstance(void)
{
	static auto p = new ScoreInfo();
	CC_SAFE_RETAIN(p);
	p->autorelease();
	return p;
}

void ScoreInfo::Save(std::string& key)
{
	cocos2d::UserDefault* data = cocos2d::UserDefault::getInstance();
	data->setIntegerForKey(key.c_str(), _scoreNum);
	data->flush();
}

void ScoreInfo::Load(std::string& key)
{
	_highScore = cocos2d::UserDefault::getInstance()->getIntegerForKey(key.c_str());
}

bool ScoreInfo::Reset(void)
{
	_scoreNum = 0;
	return true;
}

bool ScoreInfo::AddScore(int num)
{
	_scoreNum += num;
	return true;
}

void ScoreInfo::update(float dt)
{
	_number->setNumber(_scoreNum);
}

ScoreInfo::ScoreInfo()
{
	_scoreNum = 0;
	_highScore = 0;
	_number = Number::create();
	_number->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	_number->setPosition(200, 500);
	_number->setSpan(40);
	_number->setPrefix("number");
	addChild(_number);

	this->autorelease();

	scheduleUpdate();
}
