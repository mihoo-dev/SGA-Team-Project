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

    for (int i = 0; i < 1; i++)
    {
        Object * bubble = new Bubble;
        if (i == 0)
            bubble->init(521, 401);
        else if (i == 1)
            bubble->init(432, 400);
        else if (i == 2)
            bubble->init(322, 805);
        else if (i == 3)
            bubble->init(457, 922);
        else if (i == 4)
            bubble->init(533, 922);
        else if (i == 5)
            bubble->init(587, 922);
        else if (i == 6)
            bubble->init(896, 788);

        _vObject.push_back(bubble);
    }

    return S_OK;
}

void TutorialScene::release()
{
    _pm->release();
    for (int i = 0; i < _vObject.size(); i++)
    {
        _vObject[i]->release();
        SAFE_DELETE(_vObject[i]);
    }
    _vObject.clear();
}

void TutorialScene::update()
{
    _pm->update();

    for (int i = 0; i < _vObject.size(); i++)
    {
        _vObject[i]->Collision(_pm->GetRC());
        _vObject[i]->update();

        if (!_vObject[i]->GetInUse())
        {
            _vObject[i]->release();
            SAFE_DELETE(_vObject[i]);
            _vObject.erase(_vObject.begin() + i);
        }
    }

    FadeOut(&_alpha);
}

void TutorialScene::render()
{
    IMAGEMANAGER->findImage("background")->render(getMemDC(),
        CAMERA->GetX(), CAMERA->GetY(),
        CAMERA->GetX(), CAMERA->GetY(),
        WINSIZEX, WINSIZEY);

    _pm->render();

    for (int i = 0; i < _vObject.size(); i++)
        _vObject[i]->render();

    IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);
}
