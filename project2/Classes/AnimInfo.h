#pragma once
#include <map>
#include <string>
#include <cocos2d.h>

// Animate管理用
using AnimData = std::map<std::string, cocos2d::Animate*>;

class AnimInfo
{
public:
	AnimInfo();
	~AnimInfo();

	// アニメーションを追加します
	// <param = plist> plistのパス
	// <param = key>   取得用のキー
	// <param = delay> 再生間隔
	// <param = restoreOriginalFrame> 最初のコマに戻すか
	void AddAnim(const std::string& plist,const std::string& key, int num, const float& delay,bool restoreOriginalFrame);
	// Animateを取得します
	// <param = key> 登録したキー
	cocos2d::Animate* GetData(const std::string& key);
private:
	AnimData _data;
};

