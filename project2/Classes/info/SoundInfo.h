#pragma once
#include <string>
#include <map>
#include <ck/sound.h>
#include <cocos2d.h>

using SoundList = std::map<std::string, CkSound*>;

class SoundInfo:public cocos2d::Node
{
public:
	static SoundInfo& getInstance(void);
	// 読み込み
	bool LoadStreamFile(std::string filename, std::string key);
	bool LoadBankFile(std::string filename);
	// 再生
	bool PlayStreamFile(std::string key, int loopCount = -1);
	bool PlayBankFile(std::string key);
	// 一時停止
	void PauseAll(void);
	// 再開
	void ResumeAll(void);
	void update(float dt);

private:
	SoundInfo();
	~SoundInfo();

	SoundList _bgms;
	SoundList _ses;
};

