#include "stdafx.h"
#include "ClearScene.h"


ClearScene::ClearScene()
{
    
}


ClearScene::~ClearScene()
{
}

HRESULT ClearScene::init()
{
    CAMERA->SetPos(0, 0);
    CAMERA->SetSize(600, 500);

    IMAGEMANAGER->addImage("EndScene", "EndScene.bmp", 600, 500, false, NULL);

    _sceneStart = true;
    _alpha = 255;

    SOUNDMANAGER->allStop();
    SOUNDMANAGER->play("CLEAR", 1.0f);

    return S_OK;
}

void ClearScene::release()
{
}

void ClearScene::update()
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

void ClearScene::render()
{
    IMAGEMANAGER->findImage("EndScene")->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY());
    IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetX(), CAMERA->GetY(), _alpha);
}
