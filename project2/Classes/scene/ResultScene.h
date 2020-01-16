#pragma once
#include <cocos2d.h>

class ResultScene :public cocos2d::Scene 
{
public:
	static cocos2d::Scene* createScene();
	bool init()override;
	CREATE_FUNC(ResultScene);
private:
	void ChangeScene(cocos2d::Ref* pSender);
};