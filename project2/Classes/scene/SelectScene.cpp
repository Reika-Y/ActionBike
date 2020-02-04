#include "SelectScene.h"
#include "GameScene.h"
#include "../info/SoundInfo.h"

cocos2d::Scene* SelectScene::createScene()
{
	return SelectScene::create();
}

bool SelectScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto s_size = cocos2d::Director::getInstance()->getVisibleSize();

	auto startButton = cocos2d::MenuItemImage::create(
		"img/ui/button1.png",
		"img/ui/button2.png",
		CC_CALLBACK_1(SelectScene::ChangeScene, this));
	startButton->setPosition(cocos2d::Vec2(s_size.width / 2, 200));
	auto menu = cocos2d::Menu::create(startButton, NULL);
	menu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(menu, 1);

	auto bg = cocos2d::Sprite::create("img/background/select.png");
	bg->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	addChild(bg);

	SoundInfo::getInstance().LoadStreamFile("sound/bgm/select.cks", "select");
	SoundInfo::getInstance().PlayStreamFile("select");

	return true;
}

void SelectScene::ChangeScene(cocos2d::Ref* pSender)
{
	StageInfo info;
	info.bgName = "img/background/main.png";
	info.stage = "test";

	auto scene = GameScene::createScene();
	dynamic_cast<GameScene*>(scene)->SetStage(info);
	cocos2d::Director::getInstance()->replaceScene(scene);
}
