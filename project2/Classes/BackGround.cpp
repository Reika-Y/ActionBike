#include "BackGround.h"

bool BackGround::init()
{
	_data.clear();
	setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	setPosition(cocos2d::Vec2::ZERO);
	_size = cocos2d::Director::getInstance()->getVisibleSize();
	scheduleUpdate();
	return true;
}

void BackGround::AddImage(std::string filename, float _speed)
{
	auto node = cocos2d::SpriteBatchNode::create(filename);
	node->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	addChild(node);

	auto num = NumberOfSheet(node->getTexture()->getContentSize());
	for (int i = 0; i < num; i++)
	{
		auto sp = cocos2d::Sprite::createWithTexture(node->getTexture());
		sp->setAnchorPoint(cocos2d::Vec2::ZERO);
		sp->setPosition(sp->getContentSize().width * i, 0);
		node->addChild(sp);

		_data.emplace_back(BgData{ sp, _speed, num });
	}
}

void BackGround::update(float dt)
{
	for (auto data : _data)
	{
		data._sprite->setPosition((data._sprite->getPosition().x - data._speed), 0);
		if (data._sprite->getPosition().x + data._sprite->getContentSize().width <= 0)
		{
			data._sprite->setPosition(data._sprite->getContentSize().width * (data.num - 1), 0);
		}
	}
}

int BackGround::NumberOfSheet(cocos2d::Size size)
{
	int num = size.width / size.width;
	// 画像の横幅が画面のサイズより小さければ加算
	if (static_cast<int>(_size.width) % static_cast<int>(size.width) != 0)
	{
		num++;
	}
	// 両方向対応のため一枚多く返す
	return num + 1;
}
