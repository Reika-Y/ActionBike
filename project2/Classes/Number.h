#pragma once
#include <cocos2d.h>

// 数字を画像で表示するクラス
class Number:public cocos2d::Sprite
{
public:
	// 数字の画像ファイル名の設定
	void setPrefix(std::string prefix);
	void setSpan(int span);
	void setAlignCenter();
	void setNumber(int num);
	void remove(void);
	bool init()override;
	CREATE_FUNC(Number);
private:
	// 数字オブジェクトの作成
	void CreateNumber(int num);
	// 数字をクリア
	void RemoveNumber(void);

	int _num;
	int _span;
	bool _alignCenter;

	cocos2d::SpriteFrameCache* cache;
};

