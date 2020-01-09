#pragma once
#include <cocos2d.h>
#include <string>
#include <list>

struct BgData {
	cocos2d::Sprite* _sprite;
	float _speed;
	int num;
};

class BackGround:public cocos2d::Layer
{
public:
	bool init()override;
	CREATE_FUNC(BackGround);
	void AddImage(std::string filename, float _speed);
	void update(float dt)override;
private:
	int NumberOfSheet(cocos2d::Size size);
	std::list<BgData>_data;
	
	cocos2d::Size _size;

};

