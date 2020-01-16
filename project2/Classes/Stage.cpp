#include "Stage.h"

// パス
const std::string folder_path = "map/";
// 拡張子
const std::string extension = ".tmx";

// ステージ作成
// <param = filename> ステージ名
Stage* Stage::createStage(const std::string& filename, cocos2d::Node* node)
{
	Stage* p = new Stage(); 
	auto path = cocos2d::__String::createWithFormat("%s%s%s", folder_path.c_str(), filename.c_str(), extension.c_str());

	if (p && p->init(path->getCString(),node))
	{ 
		p->autorelease(); 
		return p; 
	} 
	else 
	{ 
		delete p; 
		p = nullptr; 
		return nullptr; 
	} 
	return nullptr;
}

// <param = num> ステージ番号
Stage* Stage::createStageWithNumber(int num, cocos2d::Node* node)
{
	Stage* p = new Stage();
	auto path = cocos2d::__String::createWithFormat("%s%d%s", folder_path.c_str(), num, extension.c_str());
	if (p && p->init(path->getCString(),node))
	{
		p->autorelease();
		return p;
	}
	else
	{
		delete p;
		p = nullptr;
		return nullptr;
	}
	return nullptr;
}

void Stage::update(float dt)
{
}

Stage::Stage():_tiledMap(nullptr)
{
}

Stage::~Stage()
{
	// 解放
	CC_SAFE_RELEASE_NULL(_tiledMap);
}

bool Stage::init(const std::string& filename, cocos2d::Node* node)
{
	if (!Layer::init())
	{
		return false;
	}
	auto map = cocos2d::TMXTiledMap::create(filename);
	this->addChild(map);
	this->setTiledMap(map);
	this->scheduleUpdate();

	//auto size = cocos2d::Director::getInstance()->getVisibleSize();
	//this->runAction(cocos2d::Follow::create(node/*, cocos2d::Rect(0, 0, size.width, size.height)*/));

	return true;
}
