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
	void CloseLayer(cocos2d::Ref* pSender);

	cocos2d::Layer* closeLayer;		// 終了確認ウィンドウ用
};

