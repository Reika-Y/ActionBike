#include "Stage.h"
#include <algorithm>
#include "info/EffectInfo.h"
#include "Ground.h"

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
	for (auto item : itemList)
	{
		if (item->IsErace())
		{
			EffectInfo::getInstance()->Play("effect/star", cocos2d::Vec3::ZERO, item->getPosition());
			removeChild(item);
		}
	}
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(), [](Item* item) {return item->IsErace(); }), itemList.end());
}

std::list<Item*> Stage::getItemList(void)
{
	return itemList;
}

Stage::Stage():_tiledMap(nullptr)
{
	EffectInfo::getInstance()->LoadEffect("effect/star",3);
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

	auto tmp = Ground::create(map);

	// プレイヤーの設定
	auto data = _tiledMap->getObjectGroup("player")->getObject("startPoint");
	node->setPositionX(data["x"].asFloat());
	node->setPositionY(data["y"].asFloat());

	// アイテムの設置
	itemList.clear();
	auto items = _tiledMap->getObjectGroup("item")->getObjects();
	auto batch = cocos2d::SpriteBatchNode::create("img/item.png");
	addChild(batch);
	for (auto item : items)
	{
		auto p = Item::create(batch->getTexture());
		p->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
		data = item.asValueMap();
		p->setPositionX(data["x"].asFloat());
		p->setPositionY(data["y"].asFloat());
		itemList.emplace_back(p);
		addChild(p);
	}
	scheduleUpdate();
	return true;
}
