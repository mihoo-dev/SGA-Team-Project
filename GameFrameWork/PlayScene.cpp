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
    IMAGEMANAGER->addImage("background", "background1.bmp", 687, 732, true, RGB(255, 0, 255));

    _x = WINSIZEX / 2;
    _y = WINSIZEY / 2;

    return S_OK;
}

void PlayScene::release()
{
}

void PlayScene::update()
{

    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
        _x += 3;
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
        _x -= 3;
    if (KEYMANAGER->isStayKeyDown(VK_UP))
        _y -= 3;
    if (KEYMANAGER->isStayKeyDown(VK_DOWN))
        _y += 3;

    _rc = RectMakeCenter(_x, _y, 20, 20);

    CAMERA->update(_x, _y, 3, true);
}

void PlayScene::render()
{
    IMAGEMANAGER->findImage("background")->render(getMemDC(),
        CAMERA->GetX(), CAMERA->GetY(),
        CAMERA->GetX(), CAMERA->GetY(), 
        WINSIZEX, WINSIZEY);

    Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}
