#pragma once
#include "InputBase.h"
struct InputTouch :
	public InputBase
{
	CREATE_FUNC(InputTouch);
	// 押した瞬間
	bool IsInput()override;
	// 押している
	bool IsPressing()override;
	// 入力なし
	bool IsNotInput()override;
	void update(void)override;
private:
	InputTouch();
	~InputTouch();
	bool init(void)override;
};

