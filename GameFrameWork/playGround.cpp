#include "stdafx.h"
#include "playGround.h"


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
    _playScene = new PlayScene;
    _endScene = new EndScene;
    _loadingScene = new LoadingScene;

    SCENEMANAGER->addScene("StartScene", _startScene);
    SCENEMANAGER->addScene("PlayScene", _playScene);
    SCENEMANAGER->addScene("EndScene", _endScene);
    SCENEMANAGER->addLoadingScene("LoadingScene", _loadingScene);

    SCENEMANAGER->changeScene("PlayScene");

    _sceneChange1 = false;
    _sceneChange2 = false;

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
            SCENEMANAGER->changeScene("PlayScene", "LoadingScene");
        }
    }

    if(!_sceneChange1 && !_sceneChange2)
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
