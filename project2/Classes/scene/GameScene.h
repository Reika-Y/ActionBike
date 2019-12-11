#pragma once
#include <cocos2d.h>

class GameScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init()override;
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

