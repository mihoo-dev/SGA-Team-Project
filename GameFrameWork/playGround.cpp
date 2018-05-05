#include "stdafx.h"
#include "playGround.h"

//앞으로 일주일 해야할 것들이 참 많아요~ XD

playGround::playGround()
{
}


playGround::~playGround()
{

}

//초기화 해주는 곳
HRESULT playGround::init()
{
	gameNode::init(true);

    IMAGEMANAGER->addImage("fade", "fade.bmp", 800, 600, false, RGB(0, 0, 0), true);
    _alpha = 0;

    _startScene = new StartScene;
	_worldScene = new WorldScene;
    _endScene = new EndScene;
    _loadingScene = new LoadingScene;
	_storeScene = new StoreScene;

	//스테이지씬 동적 할당
	_tutorialScene = new TutorialScene;
	_graveyardScene = new GraveyardScene;
	_snakeScene = new BossSnakeScene;
	_hotdogScene = new HotDogScene;
	_bearScene = new BossBearScene;
	_bunnyScene = new BunnyScene;

	//스테이지씬 씬매니져에 추가
	SCENEMANAGER->addScene("TutorialScene", _tutorialScene);
	SCENEMANAGER->addScene("GraveyardScene", _graveyardScene);
	SCENEMANAGER->addScene("SnakeScene", _snakeScene);
	SCENEMANAGER->addScene("HotDogScene", _hotdogScene);
	SCENEMANAGER->addScene("BearScene", _bearScene);
	SCENEMANAGER->addScene("BunnyScene", _bunnyScene);

    SCENEMANAGER->addScene("StartScene", _startScene);
	SCENEMANAGER->addScene("WorldScene", _worldScene);
    SCENEMANAGER->addScene("EndScene", _endScene);
	SCENEMANAGER->addScene("StoreScene", _storeScene);
    SCENEMANAGER->addLoadingScene("LoadingScene", _loadingScene);

    SCENEMANAGER->changeScene("StartScene");

    _sceneChange1 = false;
    _sceneChange2 = false;
	_sceneChange3 = false;
	_sceneChange4 = false;
	_sceneChange5 = false;
	_sceneChange6 = false;
	_sceneChange7 = false;
	_sceneChange8 = false;

	//사운드 추가
	//씬 백그라운드
	SOUNDMANAGER->addSound("TUTORIAL", "sound\\Candy Kingdom.mp3", true, true);
	SOUNDMANAGER->addSound("WORLDMAP", "sound\\Grasslands Overworld Theme.mp3", true, true);
	SOUNDMANAGER->addSound("GRAVEYARD", "sound\\Graveyard.mp3", true, true);
	SOUNDMANAGER->addSound("SNAKE", "sound\\Red Rock Pass VS.mp3", true, true);
	SOUNDMANAGER->addSound("VICTORY", "sound\\Victory (VS).mp3", true, false);
	SOUNDMANAGER->addSound("HOTDOG", "sound\\Housie Village.mp3", true, true);
	SOUNDMANAGER->addSound("STORE", "sound\\Grass Lands.mp3", true, true);

	//이펙트
	SOUNDMANAGER->addSound("ENTER", "sound\\Door of the Doorlord.mp3", true, false);	
	SOUNDMANAGER->addSound("PUNCH1", "sound\\EFFECT_PUNCH1.mp3", false, false);
	SOUNDMANAGER->addSound("PUNCH2", "sound\\EFFECT_PUNCH2.mp3", false, false);
	SOUNDMANAGER->addSound("GROWL", "sound\\EFFECT_GROWL.mp3", false, false);
	SOUNDMANAGER->addSound("GETBRIDGE", "sound\\EFFECT_GETBRIDGE.mp3", false, false);
	SOUNDMANAGER->addSound("START", "sound\\EFFECT_START.mp3", false, false);
    SOUNDMANAGER->addSound("JUMP", "sound\\Jump.mp3", false, false);
    SOUNDMANAGER->addSound("BUTTON", "sound\\Button.mp3", false, false);
    SOUNDMANAGER->addSound("ITEM", "sound\\ItemGet.mp3", false, false);
    SOUNDMANAGER->addSound("GAMEOVER", "sound\\GameOver.mp3", false, false);





	return S_OK;
}

//메모리 해제 (동적할당 해제등)
void playGround::release()
{
	gameNode::release();

    SCENEMANAGER->release();
}

//연산
void playGround::update()
{
	gameNode::update();

    if (KEYMANAGER->isOnceKeyDown('Q'))
        _sceneChange1 = true;
    if (KEYMANAGER->isOnceKeyDown('W'))
        _sceneChange2 = true;
	if (KEYMANAGER->isOnceKeyDown('E'))
		_sceneChange3 = true;
	if (KEYMANAGER->isOnceKeyDown('R'))
		_sceneChange4 = true;
	if (KEYMANAGER->isOnceKeyDown('T'))
		_sceneChange5 = true;
	if (KEYMANAGER->isOnceKeyDown('Y'))
		_sceneChange6 = true;
	if (KEYMANAGER->isOnceKeyDown('K'))
		_sceneChange7 = true;
	if (KEYMANAGER->isOnceKeyDown('L'))
		_sceneChange8 = true;

    if (_sceneChange1)
    {
        if (FadeIn(&_alpha))
        {
            _sceneChange1 = false;
            SCENEMANAGER->changeScene("StartScene", "LoadingScene");
        }
    }
    if (_sceneChange2)
    {
        if (FadeIn(&_alpha))
        {
            _sceneChange2 = false;
            SCENEMANAGER->changeScene("TutorialScene", "LoadingScene");
        }
    }
	if (_sceneChange3)
	{
		if (FadeIn(&_alpha))
		{
			_sceneChange3 = false;
			SCENEMANAGER->changeScene("WorldScene", "LoadingScene");
		}
	}
	if (_sceneChange4)
	{
		if (FadeIn(&_alpha))
		{
			_sceneChange4 = false;
			SCENEMANAGER->changeScene("GraveyardScene", "LoadingScene");
		}
	}
	if (_sceneChange5)
	{
		if (FadeIn(&_alpha))
		{
			_sceneChange5 = false;
			SCENEMANAGER->changeScene("StoreScene", "LoadingScene");
		}
	}
	if (_sceneChange6)
	{
		if (FadeIn(&_alpha))
		{
			_sceneChange6 = false;
			SCENEMANAGER->changeScene("HotDogScene", "LoadingScene");
		}
	}
	if (_sceneChange7)
	{
		if (FadeIn(&_alpha))
		{
			_sceneChange7 = false;
			SCENEMANAGER->changeScene("BearScene", "LoadingScene");
		}
	}
	if (_sceneChange8)
	{
		if (FadeIn(&_alpha))
		{
			_sceneChange8 = false;
			SCENEMANAGER->changeScene("BunnyScene", "LoadingScene");
		}
	}
    if(!_sceneChange1 
		&& !_sceneChange2 
		&& !_sceneChange3 
		&& !_sceneChange4 
		&& !_sceneChange5
		&& !_sceneChange6
		&& !_sceneChange7
		&& !_sceneChange8)

        FadeOut(&_alpha);
        
    
    SCENEMANAGER->update();
	EFFECTMANAGER->update();
}

//그려주는
void playGround::render()
{
    SCENEMANAGER->render();

    TIMEMANAGER->render(getMemDC());

    IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);
	//this->getBackBuffer()->render(getHDC(), 0, 0);
    CAMERA->render(getHDC());
}
