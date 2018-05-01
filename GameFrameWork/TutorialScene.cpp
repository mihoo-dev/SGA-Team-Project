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
    IMAGEMANAGER->addImage("TutoBackground", "TutoBackground.bmp", 1374, 688, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("background", "background1.bmp", 1374, 1464, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("backgroundCol", "backgroundCol.bmp", 1374, 1464, true, RGB(255, 0, 255));


    _pm = new PlayerManager;
    _pm->init();

    for (int i = 0; i < 13; i++)
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
        else if (i == 7)
            bubble->init(917, 886);
        else if (i == 8)
            bubble->init(1023, 873);
        else if (i == 9)
            bubble->init(1140, 888);
        else if (i == 10)
            bubble->init(387, 1362);
        else if (i == 11)
            bubble->init(272, 1375);
        else if (i == 12)
            bubble->init(711, 1375);

        _vObject.push_back(bubble);
    }

    Object * door = new Door;
    door->init(106, 1371);

    _vObject.push_back(door);

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
    _pm->GroundCollision("backgroundCol");
    _pm->update();

    for (int i = 0; i < _vObject.size(); i++)
    {
        if(_vObject[i]->GetName() == "TutoBubble")
            _vObject[i]->Collision(_pm->GetPlayerHitRC());
        if (_vObject[i]->GetName() == "Door")
            _vObject[i]->Collision(_pm->GetPlayerColRC());
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
    IMAGEMANAGER->findImage("TutoBackground")->render(getMemDC(),
        CAMERA->GetX(), CAMERA->GetY(),
        CAMERA->GetX() * 0.00001, CAMERA->GetY() * 0.000001,
        WINSIZEX, WINSIZEY);

    IMAGEMANAGER->findImage("background")->render(getMemDC(),
        CAMERA->GetX(), CAMERA->GetY(),
        CAMERA->GetX(), CAMERA->GetY(),
        WINSIZEX, WINSIZEY);

    for (int i = 0; i < _vObject.size(); i++)
        _vObject[i]->render();

    _pm->render();

    IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);
}