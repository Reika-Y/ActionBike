#include "GameScene.h"
#include "actor/Player.h"
#include "BackGround.h"
#include "Stage.h"

cocos2d::Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = cocos2d::MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(cocos2d::Vec2(x, y));
	}
	auto menu = cocos2d::Menu::create(closeItem, NULL);
	menu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(menu, 1);

	//auto sp = cocos2d::Sprite::create("img/bike1.png");
	//sp->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	//sp->setPosition(cocos2d::Vec2(300, 300));
	//this->addChild(sp);

	auto bg = BackGround::create();
	bg->AddImage("img/Environment/background.png", 1.f);
	bg->AddImage("img/Environment/middleground.png", 2.f);
	addChild(bg);

	auto stage = Stage::createStage("test");
	addChild(stage);

	auto player = Player::create();
	addChild(player);
	return true;
}

void GameScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	cocos2d::Director::getInstance()->end();
}
