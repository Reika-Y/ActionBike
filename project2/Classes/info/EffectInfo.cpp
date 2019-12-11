#include "EffectInfo.h"

const std::string extension = ".efk";

EffectInfo::~EffectInfo()
{
	// エミッターの削除
	for (auto i : _emitters)
	{
		delete(i);
	}
	_emitters.clear();
	// マネージャーの破棄
	_manager->release();
}

EffectInfo* EffectInfo::getInstance(void)
{
	static EffectInfo* _effect = new EffectInfo();
	return _effect;
}

void EffectInfo::begin(cocos2d::Renderer* renderer, float globalZOrder)
{
	_manager->begin(renderer, globalZOrder);
}

void EffectInfo::end(cocos2d::Renderer* renderer, float globalZOrder)
{
	_manager->end(renderer, globalZOrder);
}

bool EffectInfo::LoadEffect(std::string filename, float scale)
{
	if (_effectList.find(filename) != _effectList.end())
	{
		return false;
	}
	auto effect = efk::Effect::create(filename + extension, scale);
	effect->retain();
	_effectList.emplace(filename, effect);
	return true;
}

// 再生
void EffectInfo::Play(std::string key, const cocos2d::Vec3& rotation, const cocos2d::Vec2& pos)
{
	for (auto emitter : _emitters)
	{
		if (!emitter->isPlaying())
		{
			emitter->setEffect(_effectList[key]);
			emitter->setPlayOnEnter(true);
			emitter->setRotation3D(rotation);
			emitter->setPosition(pos);
			cocos2d::Director::getInstance()->getRunningScene()->addChild(emitter);
			return;
		}
	}

	auto emitter = efk::EffectEmitter::create(_manager);
	emitter->setEffect(_effectList[key]);
	emitter->setPlayOnEnter(true);
	emitter->setRotation3D(rotation);
	emitter->setPosition(pos);
	emitter->retain();
	_emitters.emplace_back(emitter);
	cocos2d::Director::getInstance()->getRunningScene()->addChild(emitter);
}

void EffectInfo::update(float dt)
{
	_manager->update();
}

EffectInfo::EffectInfo()
{
	auto rsize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	_manager = efk::EffectManager::create(rsize);
	scheduleUpdate();
	autorelease();
}
