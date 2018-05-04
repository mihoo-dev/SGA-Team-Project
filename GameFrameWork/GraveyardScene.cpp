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
	IMAGEMANAGER->addImage("STAGE_GRAVEYARD_BACKGROUND", "image\\STAGE_GRAVEYARD_BACKGROUND.bmp", 7168, 510, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_GRAVEYARD", "image\\STAGE_GRAVEYARD.bmp", 7168, 510, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_GRAVEYARD_PIXEL", "image\\STAGE_GRAVEYARD_PIXEL.bmp", 7168, 510, true, RGB(255, 0, 255));

	SOUNDMANAGER->addSound("GRAVEYARD", "sound\\Graveyard.mp3", true, true);
	SOUNDMANAGER->allStop();
	SOUNDMANAGER->play("GRAVEYARD", 0.5f);
	CAMERA->SetSize(7168, 510);

	//_em->setSmallZombie(WINSIZEX / 2 + 150, WINSIZEY / 2);
	//_em->setSmallZombie(WINSIZEX / 2 + 120, WINSIZEY / 2);
	//_em->setSmallZombie(WINSIZEX / 2 + 130, WINSIZEY / 2);
	//_em->setSmallZombie(WINSIZEX / 2 + 140, WINSIZEY / 2);
	//_em->setSmallZombie(WINSIZEX / 2 + 110, WINSIZEY / 2);

	_pm = new PlayerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();

	_em->setSmallZombie(WINSIZEX / 2 + 300, WINSIZEY / 2);
	_em->setSmallZombie(WINSIZEX / 2 + 150, WINSIZEY / 2);
	_em->setSmallZombie(WINSIZEX / 2 + 120, WINSIZEY / 2);
	_em->setSmallZombie(WINSIZEX / 2 + 130, WINSIZEY / 2);
	_em->setSmallZombie(WINSIZEX / 2 + 140, WINSIZEY / 2);
	_em->setSmallZombie(WINSIZEX / 2 + 110, WINSIZEY / 2);

	return S_OK;
}

void GraveyardScene::release()
{
	_pm->release();
	_em->release();
}

void GraveyardScene::update()
{
    _pm->GetPlayer()->GroundCollision("STAGE_GRAVEYARD_PIXEL");
	_pm->update();

	_em->update(_pm, "STAGE_GRAVEYARD_PIXEL");
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
	_em->render();
	_pm->render();

}