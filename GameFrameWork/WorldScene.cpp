#include "stdafx.h"
#include "WorldScene.h"
#include "World.h"

WorldScene::WorldScene()
{
}


WorldScene::~WorldScene()
{
}

HRESULT WorldScene::init()
{

	_world = new World;
	_world->init(WORLDXY->GetWorldX(), WORLDXY->GetWorldY());

	CAMERA->SetSize(2793, 2111);
	CAMERA->SetPos(-(WORLDXY->GetWorldX() - WINSIZEX / 2), -(WORLDXY->GetWorldY() - WINSIZEY / 2));
	
	SOUNDMANAGER->allStop();
	SOUNDMANAGER->play("WORLDMAP", 0.5f);

	return S_OK;
}

void WorldScene::release()
{
	_world->release();
}

void WorldScene::update()
{
	_world->update();
}

void WorldScene::render()
{	//¿ùµå¸Ê ·»´õ
	IMAGEMANAGER->addImage("WORLD_MAP", "WORLD_MAP.bmp", 2793, 2111, false, NULL)->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY(), CAMERA->GetX(), CAMERA->GetY(), 600, 500);
	
	_world->render();
}
