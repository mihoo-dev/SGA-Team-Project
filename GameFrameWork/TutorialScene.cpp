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
	SOUNDMANAGER->allStop();
	SOUNDMANAGER->play("TUTORIAL", 0.5f);

    IMAGEMANAGER->addImage("TutoBackground", "TutoBackground.bmp", 1374, 688, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("background", "background1.bmp", 1374, 1464, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("backgroundCol", "backgroundCol.bmp", 1374, 1464, true, RGB(255, 0, 255));

    CAMERA->SetPos(0, 0);
    CAMERA->SetSize(1374, 1464);
    
    _pm = new PlayerManager;
    _pm->init(1220, 425);

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

    _alpha = 255;
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
    _pm->GetPlayer()->GroundCollision("backgroundCol");
    _pm->update();

    for (int i = 0; i < _vObject.size(); i++)
    {
        _vObject[i]->Collision(_pm->GetPlayer());
        /*if(_vObject[i]->GetName() == "TutoBubble")
            _vObject[i]->Collision(_pm->GetPlayer()->GetHitRC());
        if (_vObject[i]->GetName() == "Door")
            _vObject[i]->Collision(_pm->GetPlayer()->GetColRC());*/
        _vObject[i]->update();

        if (!_vObject[i]->GetInUse())
        {
            _vObject[i]->release();
            SAFE_DELETE(_vObject[i]);
            _vObject.erase(_vObject.begin() + i);
        }
    }

    if(_pm->GetPlayer()->GetState() != Player::RIGHT_DOOR_ENTER && 
        _pm->GetPlayer()->GetState() != Player::LEFT_DOOR_ENTER)
        FadeOut(&_alpha);
    else
        FadeIn(&_alpha);
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

	TestText();

    IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);
}

void TutorialScene::TestText()
{
	char status[128];
	sprintf_s(status, "_x : %0.f, _y : %0.f", _pm->GetPlayer()->GetX(), _pm->GetPlayer()->GetY());
	TextOut(getMemDC(), CAMERA->GetX(), CAMERA->GetY() + 200, status, strlen(status));
}
