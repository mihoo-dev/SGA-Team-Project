#include "stdafx.h"
#include "PlayScene.h"


PlayScene::PlayScene()
{
}


PlayScene::~PlayScene()
{
}

HRESULT PlayScene::init()
{
    IMAGEMANAGER->addImage("background", "background1.bmp", 1374, 1464, true, RGB(255, 0, 255));

    _pm = new PlayerManager;
    _pm->init();

    return S_OK;
}

void PlayScene::release()
{
    _pm->release();
}

void PlayScene::update()
{
    _pm->update();
}

void PlayScene::render()
{
    IMAGEMANAGER->findImage("background")->render(getMemDC(),
        CAMERA->GetX(), CAMERA->GetY(),
        CAMERA->GetX(), CAMERA->GetY(), 
        WINSIZEX, WINSIZEY);

    _pm->render();
}
