#include "AnimInfo.h"

void AnimInfo::AddAnim(const std::string& plist, const std::string& key, int num, const float& delay, bool restoreOriginalFrame)
{
	if (_data.find(key) != _data.end())
	{
		return;
	}

	// plistの読み込み
	auto _cache = cocos2d::SpriteFrameCache::getInstance();
	_cache->addSpriteFramesWithFile(plist);
	auto _animation = cocos2d::Animation::create();

	bool isloop = true;
	for (int i = 0; i < num; i++)
	{
		auto str = cocos2d::__String::createWithFormat("%s-%d.png", key.c_str(), i+1);
		auto sprite = cocos2d::Sprite::createWithSpriteFrameName(str->getCString());
		sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
		_animation->addSpriteFrameWithTexture(sprite->getTexture(), sprite->getTextureRect());
	}
	
	_animation->setDelayPerUnit(delay);
	_animation->setRestoreOriginalFrame(restoreOriginalFrame);
	_data.emplace(key, cocos2d::Animate::create(_animation));
	CC_SAFE_RETAIN(_data[key]);
}

cocos2d::Animate* AnimInfo::GetData(const std::string& key)
{
	if (_data.find(key) == _data.end())
	{
		cocos2d::log("key is not found.");
		return nullptr;
	}
	if (!_data[key])
	{
		return nullptr;
	}
	return _data[key];
}

AnimInfo::AnimInfo()
{
	_data.clear();
}

AnimInfo::~AnimInfo()
{
	for (auto data : _data)
	{
		CC_SAFE_RELEASE(data.second);
	}
	_data.clear();
}


