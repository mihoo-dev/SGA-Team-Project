#include "stdafx.h"
#include "GraveyardScene.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

GraveyardScene::GraveyardScene()
{
}


GraveyardScene::~GraveyardScene()
{
}

HRESULT GraveyardScene::init()
{
	SOUNDMANAGER->allStop();
	SOUNDMANAGER->play("GRAVEYARD", 0.5f);
	CAMERA->SetSize(7168, 510);
	CAMERA->SetPos(0, 0);
	
	_pm = new PlayerManager;
	_pm->init(75, 399);

	_em = new EnemyManager;
	_em->init();
	_em->SetAdressPM(_pm);

	
	for (int ii = 0; ii < 13; ++ii)
	{
		if (ii == 0) _em->setSmallZombie(475 * (ii + 1), WINSIZEY / 2);
		else _em->setSmallZombie(475 * (ii + 1), 100);
	}

	_em->SetWorm(400, 409);
	_em->SetWorm(1900, 349);
	_em->SetWorm(2850, 409);
	_em->SetWorm(5400, 389);


	Object * _door = new Door;
	_door->init(6400, 295);

	_vDoor.push_back(_door);

	_alpha = 255;
	_sceneStart = true;
    _sceneChange = false;

	return S_OK;
}

void GraveyardScene::release()
{
	_pm->release();
	_em->release();
	_vDoor[0]->release();
}

void GraveyardScene::update()
{
	SceneStart();

    _vDoor[0]->update();
    _vDoor[0]->Collision(_pm->GetPlayer());

    DoorEnter();

	_em->update("STAGE_GRAVEYARD_PIXEL");
	
	GoSnakeStage();

	_pm->GetPlayer()->GroundCollision("STAGE_GRAVEYARD_PIXEL");
	_pm->update();
}

void GraveyardScene::render()
{
	IMAGEMANAGER->findImage("STAGE_GRAVEYARD_BACKGROUND")->render(getMemDC()
		, CAMERA->GetX(), CAMERA->GetY()
		, CAMERA->GetX() * 0.1, CAMERA->GetY()* 0.00001
		, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE_GRAVEYARD")->render(getMemDC()
		, CAMERA->GetX(), CAMERA->GetY()
		, CAMERA->GetX(), CAMERA->GetY()
		, WINSIZEX, WINSIZEY);

	_vDoor[0]->render();

	_em->render();
	_pm->render();

	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);

	//CheckStatus();
}

void GraveyardScene::CheckStatus()
{
	char status[128];
	sprintf_s(status, "x : %0.f , y : %0.f", _pm->GetPlayer()->GetX(), _pm->GetPlayer()->GetY());
	TextOut(getMemDC(), CAMERA->GetX(), CAMERA->GetY() - 200, status, strlen(status));
}

void GraveyardScene::SceneStart()
{
	if (_sceneStart)
	{
		FadeOut(&_alpha);
		if (_alpha == 0) _sceneStart = false;
	}
}

void GraveyardScene::DoorEnter()
{
	if (_pm->GetPlayer()->GetX() > 6399 && !_sceneChange)
	{
        _sceneChange = true;
		_pm->GetPlayer()->ChangeAnim(Player::RIGHT_DOOR_ENTER, "PlayerRightDoorEnter");	
	}

    if(_sceneChange)
        FadeIn(&_alpha);
}

void GraveyardScene::GoSnakeStage()
{
	if (!_sceneStart && _alpha == 255)
	{
		SCENEMANAGER->changeScene("SnakeScene", "LoadingScene");
	}
}
