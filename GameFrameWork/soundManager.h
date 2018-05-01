#pragma once
#include "singletonBase.h"
#include <map>

#include "inc/fmod.hpp"		//hpp파일 인클루드 해준다
#pragma comment(lib, "lib/fmodex_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER				25
#define EXTRACHANNELBUFFER		25		//여분 버퍼 25
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER


class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**>				arrSounds;
	typedef map<string, Sound**>::iterator		arrSoundsIter;

	typedef map<string, Channel**>				arrChannels;
	typedef map<string, Channel**>::iterator	arrChannelsIter;

private:
	System*			_system;
	Sound**			_sound;
	Channel**		_channel;

	arrSounds		_mTotalSounds;
    arrChannels     _mTotalChannels;
public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string soundName, bool bgm, bool loop);

	//									0 ~ 255 -> 0.0 ~ 1.0f
	void play(string keyName, float volume = 1.0f);
	void stop(string keyName);
	void allStop();
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

};

