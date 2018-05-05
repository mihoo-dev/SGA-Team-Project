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

	//_em->setSmallZombie(WINSIZEX / 2 + 150, WINSIZEY / 2);
	//_em->setSmallZombie(WINSIZEX / 2 + 120, WINSIZEY / 2);
	//_em->setSmallZombie(WINSIZEX / 2 + 130, WINSIZEY / 2);
	//_em->setSmallZombie(WINSIZEX / 2 + 140, WINSIZEY / 2);
	//_em->setSmallZombie(WINSIZEX / 2 + 110, WINSIZEY / 2);

	_pm = new PlayerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();
	_em->SetAdressPM(_pm);

	_em->setSmallZombie(WINSIZEX / 2 + 300, WINSIZEY / 2);
	_em->setSmallZombie(WINSIZEX / 2 + 150, WINSIZEY / 2);
	_em->setSmallZombie(WINSIZEX / 2 + 120, WINSIZEY / 2);
	_em->setSmallZombie(WINSIZEX / 2 + 130, WINSIZEY / 2);
	_em->setSmallZombie(WINSIZEX / 2 + 140, WINSIZEY / 2);
	_em->setSmallZombie(WINSIZEX / 2 + 110, WINSIZEY / 2);

	Object * _door = new Door;
	_door->init(6400, 295);

	_vDoor.push_back(_door);

	_alpha = 255;
	_sceneStart = true;


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

    _pm->GetPlayer()->GroundCollision("STAGE_GRAVEYARD_PIXEL");
	_pm->update();

	_em->update("STAGE_GRAVEYARD_PIXEL");

	_vDoor[0]->update();
	_vDoor[0]->Collision(_pm->GetPlayer()->GetColRC());

	DoorEnter();
	GoSnakeStage();
}

void GraveyardScene::render()
{
	IMAGEMANAGER->findImage("STAGE_GRAVEYARD_BACKGROUND")->render(getMemDC()
		, CAMERA->GetX(), CAMERA->GetY()
		, CAMERA->GetX(), CAMERA->GetY()
		, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE_GRAVEYARD")->render(getMemDC()
		, CAMERA->GetX(), CAMERA->GetY()
		, CAMERA->GetX(), CAMERA->GetY()
		, WINSIZEX, WINSIZEY);

	_vDoor[0]->render();

	_em->render();
	_pm->render();

	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);

	CheckStatus();
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
	if (_pm->GetPlayer()->GetX() > 6345)
	{
		_pm->GetPlayer()->ChangeAnim(Player::RIGHT_DOOR_ENTER, "PlayerRightDoorEnter");
		FadeIn(&_alpha);
	}
}

void GraveyardScene::GoSnakeStage()
{
	if (!_sceneStart && _alpha == 255)
	{
		SCENEMANAGER->changeScene("SnakeScene", "LoadingScene");
	}
}
