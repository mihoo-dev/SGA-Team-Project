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
    IMAGEMANAGER->findImage("fade")->render(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top);
}
