#pragma once

class Sprite;
struct ActModule;

struct Jumping
{
	bool operator()(Sprite& sp, ActModule& act);
};