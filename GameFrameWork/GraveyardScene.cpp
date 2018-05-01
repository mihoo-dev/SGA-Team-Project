#include "stdafx.h"
#include "GraveyardScene.h"
#include "PlayerManager.h"

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

	_pm = new PlayerManager;
	_pm->init();

	return S_OK;
}

void GraveyardScene::release()
{
	_pm->release();
}

void GraveyardScene::update()
{
	_pm->GroundCollision("STAGE_GRAVEYARD_PIXEL");
	_pm->update();
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
	_pm->render();
}