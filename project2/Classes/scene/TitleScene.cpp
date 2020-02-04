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
		"img/ui/button1.png",
		"img/ui/button2.png",
		CC_CALLBACK_1(TitleScene::ChangeScene, this));
	startButton->setPosition(cocos2d::Vec2(s_size.width/2, 200));

	auto menu = cocos2d::Menu::create(startButton,config, NULL);
	menu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(menu, 1);

	// 背景
	auto bg = BackGround::create();
	bg->AddImage("img/background/title/sky.png", 0);
	bg->AddImage("img/background/title/cloudy.png", 10);
	bg->AddImage("img/background/title/hill.png", 30);
	addChild(bg);

	// タイトルロゴ
	auto logo = cocos2d::Sprite::create("img/title-logo.png");
	logo->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	logo->setPosition(s_size / 2);
	addChild(logo);

	// BGM
	SoundInfo::getInstance().LoadStreamFile("sound/bgm/title.cks","title");
	SoundInfo::getInstance().PlayStreamFile("title");

	closeLayer = cocos2d::Layer::create();
	addChild(closeLayer, 300);
	auto f_font = cocos2d::Sprite::create("img/ui/font1.png");
	f_font->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	f_font->setPosition(s_size / 2);
	closeLayer->addChild(f_font);
	closeLayer->setVisible(false);

	return true;
}

// ステージを切り替える
void TitleScene::ChangeScene(cocos2d::Ref* pSender)
{
	// 次のシーン
	auto scene = SelectScene::createScene();
	// トランジション設定
	auto transition = TransitionPattern::create(2.0f, scene, "img/pattern.png", true);
	// シーン置き換え
	cocos2d::Director::getInstance()->replaceScene(transition);
}

void TitleScene::CloseLayer(cocos2d::Ref* pSender)
{
	
}
