#include "stdafx.h"
#include "StartScene.h"


StartScene::StartScene()
    :_alpha(255), _alphaCount(0),
    _alpha2(0), _sceneChange(false)
{
    
}


StartScene::~StartScene()
{
}

HRESULT StartScene::init()
{
	SOUNDMANAGER->addSound("TITLE", "sound\\Title Theme.mp3", true, true);
	SOUNDMANAGER->allStop();
	SOUNDMANAGER->play("TITLE", 0.5f);

    CAMERA->SetPos(0, 0);
    IMAGEMANAGER->addImage("StartScene", "StartScene.bmp", 600, 500, false, RGB(0, 0, 0));
    IMAGEMANAGER->addImage("PressStartButton", "PressStartButton.bmp", 379, 62, true, RGB(255, 0, 255), true);

    _alpha2 = 255;

    return S_OK;
}

void StartScene::release()
{
}

void StartScene::update()
{
    if(!_sceneChange)
        FadeOut(&_alpha2);

    _alphaCount += TIMEMANAGER->getElapsedTime();
    if (_alphaCount >= 0.5f)
    {
        _alphaCount = 0;
        if (_alpha == 255)
            _alpha = 0;
        else if (_alpha == 0)
            _alpha = 255;
    }

    _pressStartButton = RectMake(CAMERA->GetX() + 100, CAMERA->GetCenterY() + 150, 379, 62);

    if (PtInRect(&_pressStartButton, _ptMouse))
    {
        if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
        {
			SOUNDMANAGER->play("START", 1.0f);
            _sceneChange = true;
        }
    }

    if (_sceneChange)
    {
        if (FadeIn(&_alpha2))
        {
            _sceneChange = false;
            SCENEMANAGER->changeScene("TutorialScene", "LoadingScene");
        }
    }

    CAMERA->update(WINSIZEX / 2, WINSIZEY / 2, 10, true);
}

void StartScene::render()
{
    IMAGEMANAGER->findImage("StartScene")->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY());
    IMAGEMANAGER->findImage("PressStartButton")->alphaRender(getMemDC(), CAMERA->GetX()+100, CAMERA->GetCenterY()+150, _alpha);
    //Rectangle(getMemDC(), _pressStartButton.left, _pressStartButton.top, _pressStartButton.right, _pressStartButton.bottom);
    IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha2);
}

