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
    _tutorialScene = new TutorialScene;
	_worldScene = new WorldScene;
    _endScene = new EndScene;
    _loadingScene = new LoadingScene;

    SCENEMANAGER->addScene("StartScene", _startScene);
    SCENEMANAGER->addScene("TutorialScene", _tutorialScene);
	SCENEMANAGER->addScene("WorldScene", _worldScene);
    SCENEMANAGER->addScene("EndScene", _endScene);
    SCENEMANAGER->addLoadingScene("LoadingScene", _loadingScene);

    SCENEMANAGER->changeScene("TutorialScene");

    _sceneChange1 = false;
    _sceneChange2 = false;
	_sceneChange3 = false;

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

    if(!_sceneChange1 && !_sceneChange2 && !_sceneChange3)
        FadeOut(&_alpha);
        
    
    SCENEMANAGER->update();
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
