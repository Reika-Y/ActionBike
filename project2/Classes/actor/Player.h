#pragma once
#include "Actor.h"

class Player :
	public Actor
{
public:
	bool init(void)override;
	CREATE_FUNC(Player);
private:
	Player(){}
};

