#pragma once
#include <cocos2d.h>
#include <vector>
#include "../data/StageInfo.h"

using StageData = std::vector<StageInfo>;

class SelectScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init()override;
	CREATE_FUNC(SelectScene);
private:
	void ChangeScene(cocos2d::Ref* pSender);

	int _stageCnt;		// 1画面に表示できるステージ数
};

