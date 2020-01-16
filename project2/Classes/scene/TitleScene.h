#pragma once
#include <cocos2d.h>

class TitleScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init()override;
	CREATE_FUNC(TitleScene);
private:
	void ChangeScene(cocos2d::Ref* pSender);
};

