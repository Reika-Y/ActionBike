#pragma once
#include <cocos2d.h>
#include <array>
#include "input/InputBase.h"
#include "../ActionControl.h"
#include "../AnimInfo.h"

enum class CORNER_POINT
{
	LT,		// 左上
	LD,		// 左下
	RT,		// 右上
	RD,		// 右下
	TL,
	TR,
	BL,
	BR,
	MAX
};

using CornerPoints = std::array<cocos2d::Vec2, static_cast<int>(CORNER_POINT::MAX)>;

class Actor:public cocos2d::Sprite
{
public:
	InputBase* getInput(void);
	ActionControl& GetActionCtr(void);
	// 8点の座標を返す
	const CornerPoints& GetCornerPoints(void)const;
	bool isDie(void);
	void isDie(bool flag);
	bool isJumping(void);
	void isJumping(bool flag);
private:
protected:
	explicit Actor();
	void SetCornerPoint(cocos2d::Rect rect);

	bool _isDie = false;
	bool _isJumping = false;

	CornerPoints _corner;
	ActionControl _act;
	AnimInfo _anim;
	InputBase* _input = nullptr;
};

