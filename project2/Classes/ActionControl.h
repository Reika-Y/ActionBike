#pragma once
#include <functional>
#include <list>
#include <map>
#include <cocos2d.h>
#include "input/InputBase.h"

struct ActModule;
using ActFunc = std::function<bool(cocos2d::Sprite&, ActModule&)>;

// アクション管理用
enum class ACT_ID
{
	IDLE,		// アイドル
	RUN,
	JUMP,		// ジャンプ
	JUMPING,
	FALL,
	MAX
};

// アクション管理用モジュール
struct ActModule
{
	ACT_ID _actID;
	std::list<ACT_ID>black;
	std::list<ACT_ID>white;
	// 実行する処理のリスト
	std::list<ActFunc>_actFuncList;
	// 最終的に実行するイベント
	ActFunc _runAct;
	// 入力判定用
	InputBase* _input;
	// 衝突判定用
	std::list<int>_col;
};

// モジュール管理クラス
class ActionControl
{
public:
	ActionControl();
	~ActionControl();
	// モジュールを追加
	void AddModeule(ActModule& act);
	// モジュールの更新
	void Update(cocos2d::Sprite& sp, float dt);
	// ひとつ前のモジュールを取得
	ActModule GetOldModule(void);
	void SetNextAct(ACT_ID id);
private:
	std::map<ACT_ID, ActModule>actModeule;
	ACT_ID _oldId, _nextId;
};

