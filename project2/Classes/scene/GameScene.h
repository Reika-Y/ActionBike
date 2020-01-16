#pragma once
#include <cocos2d.h>
#include "../data/StageInfo.h"
#include "../actor/Player.h"
#include "../Stage.h"

class GameScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init()override;
	void SetStage(StageInfo info);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
	// ステージ
	CC_SYNTHESIZE_RETAIN(Stage*, _stage, stage);
	void isGoal(bool flag);
	void update(float dt)override;
private:
	void ChangeScene(float millsecond);

	bool _isGoal = false;
	Player* player;
};

