#include "SoundInfo.h"
#include <ck/ck.h>
#include <ck/platform.h>
#include <ck/bank.h>

#if CK_PLATFORM_ANDROID
#ifdef __cplusplus
extern "C"
{
#endif
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_initCricket(JNIEnv* env, jclass activity, jobject context)
	{
		CkConfig config(env, context);
		CkInit(&config);
	}
#ifdef __cplusplus
}
#endif
#endif

const std::string folder = "Resources/";

SoundInfo& SoundInfo::getInstance(void)
{
	static SoundInfo _sound;
	return _sound;
}

bool SoundInfo::LoadStreamFile(std::string filename, std::string key)
{
	if (_bgms.find(key) != _bgms.end())
	{
		return false;
	}

#if CK_PLATFORM_ANDROID
    _bgms.emplace(key, CkSound::newStreamSound((filename).c_str()));
#else
    _bgms.emplace(key, CkSound::newStreamSound((folder +filename).c_str(), CkPathType::kCkPathType_ExeDir));
#endif
	return true;
}

bool SoundInfo::LoadBankFile(std::string filename)
{
#if CK_PLATFORM_ANDROID
    auto bank = CkBank::newBank(filename.c_str());
#else
    auto bank = CkBank::newBank((folder + filename).c_str(),CkPathType::kCkPathType_ExeDir);
#endif
	const int num = bank->getNumSounds();
	for (int i = 0; i < num; i++)
	{
		_ses.emplace(bank->getSoundName(i), CkSound::newBankSound(bank, i));
	}
	return true;
}

bool SoundInfo::PlayStreamFile(std::string key, int loopCount)
{
	if (_bgms.find(key) == _bgms.end())
	{
		return false;
	}
	for (auto sound:_bgms)
	{
		if (sound.first != key && sound.second->isPlaying())
		{
			sound.second->stop();
		}
	}
	_bgms[key]->setLoopCount(loopCount);
	_bgms[key]->play();
	return true;
}

bool SoundInfo::PlayBankFile(std::string key)
{
	if (_ses.find(key) == _ses.end())
	{
		return false;
	}
	_ses[key]->play();
	return true;
}

// 一時停止
void SoundInfo::PauseAll(void)
{
	for (auto bgm : _bgms)
	{
		bgm.second->setPaused(true);
	}
	for (auto se : _ses)
	{
		se.second->setPaused(true);
	}
}

// 再開
void SoundInfo::ResumeAll(void)
{
	for (auto bgm : _bgms)
	{
		bgm.second->setPaused(false);
	}
	for (auto se : _ses)
	{
		se.second->setPaused(false);
	}
}

void SoundInfo::update(float dt)
{
	CkUpdate();
}

SoundInfo::SoundInfo()
{
#if CK_PLATFORM_ANDROID
#else 
	CkConfig config;
	CkInit(&config);
#endif
	cocos2d::Director::getInstance()->getScheduler()->schedule(schedule_selector(SoundInfo::update),this,0,false);
	_bgms.clear();
	_ses.clear();
}

SoundInfo::~SoundInfo()
{
	// bgmの破棄
	for (auto bgm : _bgms)
	{
		bgm.second->destroy();
	}
	_bgms.clear();
	// seの破棄
	for (auto se : _ses)
	{
		se.second->destroy();
	}
	_ses.clear();
	// cricketAudioのシャットダウン
	CkShutdown();
}
