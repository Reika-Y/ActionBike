﻿#include "GameScene.h"
#include "BackGround.h"
#include "ResultScene.h"
#include "../info/ScoreInfo.h"
#include "../info/EffectInfo.h"

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

	//// add a "close" icon to exit the progress. it's an autorelease object
	//auto closeItem = cocos2d::MenuItemImage::create(
	//	"CloseNormal.png",
	//	"CloseSelected.png",
	//	CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	//if (closeItem == nullptr ||
	//	closeItem->getContentSize().width <= 0 ||
	//	closeItem->getContentSize().height <= 0)
	//{
	//	return false;
	//}
	//else
	//{
	//	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	//	float y = origin.y + closeItem->getContentSize().height / 2;
	//	closeItem->setPosition(cocos2d::Vec2(x, y));
	//}
	//auto menu = cocos2d::Menu::create(closeItem, NULL);
	//menu->setPosition(cocos2d::Vec2::ZERO);
	//this->addChild(menu, 100);

	player = Player::create();
	player->setCameraMask(static_cast<int>(cocos2d::CameraFlag::USER1));
	addChild(player,1);

	addChild(ScoreInfo::getInstance(),10);

	// カメラの生成
	_cam = cocos2d::Camera::createOrthographic(visibleSize.width, visibleSize.height, -768, 768);
	addChild(_cam);
	// 位置、角度，深度
	_cam->setPosition3D(cocos2d::Vec3::ZERO);
	_cam->setRotation3D(cocos2d::Vec3::ZERO);
	_cam->setDepth(0.f);
	// マスク
	_cam->setCameraFlag(cocos2d::CameraFlag::USER1);

	//addChild(EffectInfo::getInstance());

	// 待機
	auto sp = cocos2d::Sprite::create("img/ui/ready.png");
	sp->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	sp->setPosition(visibleSize / 2);
	addChild(sp,50);

	scheduleUpdate();
	return true;
}

void GameScene::SetStage(StageInfo info)
{
	auto bg = cocos2d::Sprite::create(info.bgName);
	bg->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	addChild(bg);

	_stage = Stage::createStage(info.stage, player);
	addChild(_stage);
	_stage->setCameraMask(static_cast<int>(cocos2d::CameraFlag::USER1));
}

void GameScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	cocos2d::Director::getInstance()->end();
}

void GameScene::isGoal(bool flag)
{
	_isGoal = flag;
}

void GameScene::update(float dt)
{

	//_cam->setPositionX(_cam->getPositionX() + 120.f * dt);
	// ゴールした時
	//if (_isGoal)
	//{
	//	ChangeScene(dt);
	//}
	// プレイヤーが死んだ時
	if (player->isDie())
	{
		ChangeScene(dt);
	}
}

void GameScene::ChangeScene(float millsecond)
{
	auto scene = ResultScene::createScene();
	cocos2d::Director::getInstance()->replaceScene(scene);
}

void GameScene::visit(cocos2d::Renderer* renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags)
{
	EffectInfo::getInstance()->begin(renderer, _globalZOrder);
	cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
	EffectInfo::getInstance()->end(renderer, _globalZOrder);
}
