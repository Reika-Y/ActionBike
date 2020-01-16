#pragma once
#include <cocos2d.h>
#include "../Number.h"

class ScoreInfo:public cocos2d::Node
{
public:
	static ScoreInfo* getInstance(void);
	void Save(std::string &key);
	void Load(std::string& key);
	bool Reset(void);
	bool AddScore(int num);
	void update(float dt)override;
private:
	ScoreInfo();

	int _scoreNum;		// 表示用スコア
	int _highScore;		// ハイスコア表示用
	Number* _number;
};

