#pragma once
#include <cocos2d.h>
#include <map>
#include <array>

// 入力タイプ
enum class INPUT_TYPE
{
	TOUCH,
	MAX
};

// トリガー管理用
enum class TRIGGER
{
	NOW,
	OLD,
	MAX
};

// 情報
struct InputInfo
{
	cocos2d::Vec2 _position;
	bool _isFlag;
};

using InputState = std::map<TRIGGER, InputInfo>;

struct InputBase: public cocos2d::Layer
{
	// 更新処理
	virtual void update(void) = 0;
	// 押した瞬間
	virtual bool IsInput() = 0;
	// 押している
	virtual bool IsPressing() = 0;
	// 入力なし
	virtual bool IsNotInput() = 0;

protected:
	InputState _state;
};

