#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	: _system(NULL), _sound(NULL), _channel(NULL)
{
}


soundManager::~soundManager()
{

}


HRESULT soundManager::init()
{
	//FMOD사운드엔진을 사용하겠다고 초기화 선언
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	ZeroMemory(_sound, sizeof(_sound));
	ZeroMemory(_channel, sizeof(_channel));


	return S_OK;
}


void soundManager::release()
{

}


void soundManager::update()	
{
    //사운드 시스템을 계속적으로 업데이트
    _system->update();

    //볼륨이 바뀌거나 
    //재생이 끝난 사운드를 채널에서 빼내는등의 다양한
    //작업을 자동으로 해준다
}



void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
    _mTotalChannels.insert(make_pair(keyName, &_channel[_mTotalSounds.size()]));
}



//									0 ~ 255 -> 0.0 ~ 1.0f
void soundManager::play(string keyName, float volume)
{
    _system->playSound(FMOD_CHANNEL_FREE, (*_mTotalSounds[keyName]), false, _mTotalChannels[keyName]);

    (*_mTotalChannels[keyName])->setVolume(volume);
}


void soundManager::stop(string keyName)				 
{
    (*_mTotalChannels[keyName])->stop();
}

void soundManager::allStop()
{
	arrChannelsIter iter = _mTotalChannels.begin();

	int count = 0;

	for (iter; iter != _mTotalChannels.end(); ++iter, ++count)
	{
		_channel[count]->stop();
	}
}

void soundManager::pause(string keyName)			 
{
    (*_mTotalChannels[keyName])->setPaused(true);
}


void soundManager::resume(string keyName)			 
{
    (*_mTotalChannels[keyName])->getPaused(false);
}



bool soundManager::isPlaySound(string keyName) 
{
	bool isPlay;

    (*_mTotalChannels[keyName])->isPlaying(&isPlay);

	return isPlay;
}


bool soundManager::isPauseSound(string keyName)
{
	bool isPause;

    (*_mTotalChannels[keyName])->getPaused(&isPause);

	return isPause;
}

