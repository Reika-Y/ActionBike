#pragma once
#include <cocos2d.h>

class Item:public cocos2d::Sprite
{
public:
	static Item* create(cocos2d::Texture2D* t);
	bool init(cocos2d::Texture2D* t);
	const int Score(void);
	// 削除判定
	bool IsErace(void);
	void IsErace(bool flag);
private:
	int _score;
	bool _isErace;
};

