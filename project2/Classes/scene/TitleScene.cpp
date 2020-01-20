#include "TitleScene.h"
#include "SelectScene.h"

cocos2d::Scene* TitleScene::createScene()
{
	return TitleScene::create();
}

bool TitleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto s_size = cocos2d::Director::getInstance()->getVisibleSize();

	auto startButton = cocos2d::MenuItemImage::create(
		"img/ui/button1.png",
		"img/ui/button2.png",
		CC_CALLBACK_1(TitleScene::ChangeScene, this));
	startButton->setPosition(cocos2d::Vec2(s_size.width/2, 200));
	auto menu = cocos2d::Menu::create(startButton, NULL);
	menu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(menu, 1);

	auto bg = cocos2d::Sprite::create("img/background/title.png");
	bg->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	addChild(bg);

	auto logo = cocos2d::Sprite::create("img/title-logo.png");
	logo->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	logo->setPosition(s_size / 2);
	addChild(logo);

	return true;
}

void TitleScene::ChangeScene(cocos2d::Ref* pSender)
{
	auto scene = SelectScene::createScene();
	cocos2d::Director::getInstance()->replaceScene(scene);
}
