#include "EffectInfo.h"
#include <algorithm>

// エミッターの生存時間
const float emitterLimit = 5.0f;

const std::string extension = ".efk";

EffectInfo::~EffectInfo()
{
	// エミッターの削除
	for (auto i : _emitters)
	{
		delete(i.first);
	}
	_emitters.clear();
	// マネージャーの破棄
	_manager->release();
}

EffectInfo* EffectInfo::getInstance(void)
{
	static EffectInfo* _effect = new EffectInfo();
	CC_SAFE_RETAIN(_effect);
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
		if (!emitter.first->isPlaying())
		{
			emitter.first->setEffect(_effectList[key]);
			emitter.first->setPlayOnEnter(true);
			emitter.first->setRotation3D(rotation);
			emitter.first->setPosition(pos);
			emitter.second = 0.f;
			cocos2d::Director::getInstance()->getRunningScene()->addChild(emitter.first);
			return;
		}
	}

	auto emitter = efk::EffectEmitter::create(_manager);
	emitter->setEffect(_effectList[key]);
	emitter->setPlayOnEnter(true);
	emitter->setRotation3D(rotation);
	emitter->setPosition(pos);
	emitter->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	emitter->retain();
	_emitters.emplace_back(emitter,0.f);
	cocos2d::Director::getInstance()->getRunningScene()->addChild(emitter);
}

void EffectInfo::update(float dt)
{
	_manager->update();

	//// 使わないエミッターは消す
	//for (auto& emitter : _emitters)
	//{
	//	if (!emitter.first->isPlaying())
	//	{
	//		// 再生中でないなら、加算
	//		emitter.second += dt;
	//	}
	//	if (emitter.second > emitterLimit)
	//	{
	//		// 制限時間を超えたら削除
	//		auto scene = cocos2d::Director::getInstance()->getRunningScene();
	//		delete emitter.first;
	//		//cocos2d::Director::getInstance()->getRunningScene()->removeChild(emitter.first);
	//	}
	//}
	//_emitters.erase(std::remove_if(_emitters.begin(), _emitters.end(), [](EmmitData& data) {return !data.first; }), _emitters.end());
}

EffectInfo::EffectInfo()
{
	auto rsize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	_manager = efk::EffectManager::create(rsize);
	cocos2d::Director::getInstance()->getScheduler()->schedule(schedule_selector(EffectInfo::update), this, 0, false);
	autorelease();
}
