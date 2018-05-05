#include "stdafx.h"
#include "EndScene.h"


EndScene::EndScene()
{
}


EndScene::~EndScene()
{
}

HRESULT EndScene::init()
{
    CAMERA->SetPos(0, 0);
    CAMERA->SetSize(600, 500);

    IMAGEMANAGER->addImage("GameOver", "GameOver.bmp", 600, 500, false, NULL);

    _sceneStart = true;
    _alpha = 255;

    return S_OK;
}

void EndScene::release()
{
}

void EndScene::update()
{
    if (_sceneStart)
    {
        if (FadeOut(&_alpha)) _sceneStart = false;
    }
    if (!_sceneStart)
    {
        if (FadeIn(&_alpha))
            SCENEMANAGER->changeScene("StartScene", "LoadingScene");
    }
}

void EndScene::render()
{
    IMAGEMANAGER->findImage("GameOver")->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY());
    IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetX(), CAMERA->GetY(), _alpha);
}
