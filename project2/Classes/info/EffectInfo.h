#pragma once
#include <cocos2d.h>
#include <map>
#include <string>
#include <list>
#include "../effekseer/Effekseer.h"

using EffectList =std::map<std::string, efk::Effect*>;
using EmmitData = std::pair<efk::EffectEmitter*, float>;

class EffectInfo:public cocos2d::Node
{
public:
	~EffectInfo();
	static EffectInfo* getInstance(void);
	void begin(cocos2d::Renderer* renderer, float globalZOrder);
	void end(cocos2d::Renderer* renderer, float globalZOrder);
	bool LoadEffect(std::string filename, float scale = 1.0f);
	void Play(std::string key, const cocos2d::Vec3& rotation, const cocos2d::Vec2& pos);
	void update(float dt)override;
private:
	EffectInfo();
	EffectList _effectList;
	efk::EffectManager* _manager;
	std::list<EmmitData> _emitters;
};

