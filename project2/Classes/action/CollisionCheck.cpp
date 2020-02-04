#include <cocos2d.h>
#include "CollisionCheck.h"
#include "../ActionControl.h"
#include "../scene/GameScene.h"
#include "../actor/Actor.h"

const int id[] = { 4,39 };

bool CollisionCheck::operator()(cocos2d::Sprite& sp, ActModule& act,float& dt)
{
	auto stage = dynamic_cast<GameScene*>(cocos2d::Director::getInstance()->getRunningScene())->getstage();
	auto layer = stage->getTiledMap()->getLayer("terrain");
	auto goal= stage->getTiledMap()->getLayer("goal");
	auto mapSize = stage->getTiledMap()->getMapSize();
	auto tileSize = stage->getTiledMap()->getTileSize();

	auto col = dynamic_cast<Actor&>(sp).GetCornerPoints();

	for (auto num : act._col)
	{
		int x = col[num].x / tileSize.width;
		int y = ((mapSize.height * tileSize.height) - col[num].y) / (tileSize.height);

		if (x < 0 || mapSize.width <= x || y < 0 || mapSize.height <= y)
		{
			// ステージ範囲外なら死亡
			dynamic_cast<Actor&>(sp).isDie(true);
			return false;
		}

		int n = 0;
		n= goal->getTileGIDAt(cocos2d::Vec2(x, y));
		if (n != 0)
		{
			dynamic_cast<GameScene*>(cocos2d::Director::getInstance()->getRunningScene())->isGoal(true);
			return true;
		}

		n = layer->getTileGIDAt(cocos2d::Vec2(x, y));
		if (n != 0)
		{
			// 補正
			if (dynamic_cast<Actor*>(&sp)->getActId() == ACT_ID::FALL)
			{
				sp.setPositionY((mapSize.height - y)*tileSize.height + 1);
			}
			return false;

		}
	}
	return true;
}
