#pragma once
#include <cocos2d.h>

class SelectScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init()override;
	CREATE_FUNC(SelectScene);
private:
	void ChangeScene(cocos2d::Ref* pSender);
};

