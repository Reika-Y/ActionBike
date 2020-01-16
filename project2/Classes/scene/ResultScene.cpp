#include "ResultScene.h"

cocos2d::Scene* ResultScene::createScene()
{
	return ResultScene::create();
}

bool ResultScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto bg = cocos2d::Sprite::create("img/background/result.png");
	bg->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	addChild(bg); 

	return true;
}

void ResultScene::ChangeScene(cocos2d::Ref* pSender)
{
}
