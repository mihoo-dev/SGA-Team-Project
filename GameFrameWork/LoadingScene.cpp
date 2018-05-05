#include "stdafx.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene()
{
    
}


LoadingScene::~LoadingScene()
{
}

HRESULT LoadingScene::init()
{
    CAMERA->SetPos(0, 0);
    
    return S_OK;
}

void LoadingScene::release()
{
}

void LoadingScene::update()
{
}

void LoadingScene::render()
{
    IMAGEMANAGER->findImage("fade")->render(getMemDC(), 0, 0);
}
