#include "stdafx.h"
#include "TutorialScene.h"


TutorialScene::TutorialScene() :
    _alpha(255)
{
}


TutorialScene::~TutorialScene()
{
}

HRESULT TutorialScene::init()
{
    IMAGEMANAGER->addImage("background", "background1.bmp", 1374, 1464, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("backgroundCol", "backgroundCol.bmp", 1374, 1464, true, RGB(255, 0, 255));

    _pm = new PlayerManager;
    _pm->init();

    return S_OK;
}

void TutorialScene::release()
{
    _pm->release();
}

void TutorialScene::update()
{
    _pm->update();

    FadeOut(&_alpha);
}

void TutorialScene::render()
{
    IMAGEMANAGER->findImage("background")->render(getMemDC(),
        CAMERA->GetX(), CAMERA->GetY(),
        CAMERA->GetX(), CAMERA->GetY(), 
        WINSIZEX, WINSIZEY);

    _pm->render();

    IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);
}
