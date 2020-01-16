#pragma once
#include "Actor.h"

class Player :
	public Actor
{
public:
	bool init(void)override;
	CREATE_FUNC(Player);
	void update(float dt)override;
private:
	Player(){}
	void addModule(void);
	void addAnim(void);
};

