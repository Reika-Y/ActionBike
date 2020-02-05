#include "TitleScene.h"
#include "SelectScene.h"
#include "../info/SoundInfo.h"
#include "../BackGround.h"
#include "../transition/TransitionPattern.h"

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

	// 設定ボタン
	auto config = cocos2d::MenuItemImage::create(
		"img/ui/config1.png",
		"img/ui/config2.png",
		[](Ref * sender){
			CCLOG("Pushボタン03");
		}
	);
	config->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
	config->setPosition(s_size);

	auto startButton = cocos2d::MenuItemImage::create(
		"img/ui/button/startButton1.png",
		"img/ui/button/startButton2.png",
		CC_CALLBACK_1(TitleScene::ChangeScene, this));
	startButton->setPosition(cocos2d::Vec2(s_size.width/2, 200));

	auto menu = cocos2d::Menu::create(startButton,config, NULL);
	menu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(menu, 1);

	// 背景
	auto bg = BackGround::create();
	bg->AddImage("img/background/title/background.png", 30);
	addChild(bg);

	// タイトルロゴ
	auto logo = cocos2d::Sprite::create("img/title-logo.png");
	logo->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	logo->setPosition(s_size.width / 2,350);
	addChild(logo);

	// BGM
	SoundInfo::getInstance().LoadStreamFile("sound/bgm/title.cks","title");
	SoundInfo::getInstance().PlayStreamFile("title");

	return true;
}

// ステージを切り替える
void TitleScene::ChangeScene(cocos2d::Ref* pSender)
{
	// 次のシーン
	auto scene = SelectScene::createScene();
	// トランジション設定
	auto transition = TransitionPattern::create(1.0f, scene, "img/pattern.png", true);
	// シーン置き換え
	cocos2d::Director::getInstance()->replaceScene(transition);
}

void TitleScene::CloseLayer(cocos2d::Ref* pSender)
{
	
}
