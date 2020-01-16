#pragma once
#include <cocos2d.h>

class Stage :
	public cocos2d::Layer
{
public:
	// ステージ作成用
	static Stage* createStage(const std::string& filename,cocos2d::Node *node);
	static Stage* createStageWithNumber(int num, cocos2d::Node* node);
	// 更新
	void update(float dt)override;
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXTiledMap*, _tiledMap, TiledMap);

private:
protected:
	Stage();
	virtual ~Stage();
	bool init(const std::string& filename, cocos2d::Node*node);
};

