#include "stdafx.h"
#include "World.h"
#include "World_Character.h"


World::World()
{
}


World::~World()
{
}

HRESULT World::init()
{
	IMAGEMANAGER->addFrameImage("WORLD_FINN", "WORLD_FINN.bmp", 512, 576, 8, 9, true, RGB(255, 0, 255));

	_finn = new World_Character;
	_finn->init();

	CAMERA->SetPos(_finn->getX(), _finn->getY());

	//각 방향 움직임 애니메이션 프레임 배열
	int southMove[]		= { 8, 9, 10, 11, 12, 13 };
	int southEastMove[] = { 16, 17, 18, 19, 20, 21 };
	int eastMove[]		= { 24, 25, 26, 27, 28, 29 };
	int northEastMove[] = { 32, 33, 34, 35, 37, 37 };
	int northMove[]		= { 40, 41, 42, 43, 44, 45 };
	int northWestMove[] = { 48, 49, 50, 51, 52, 53 };
	int westMove[]		= { 56, 57, 58, 59, 60, 61 };
	int southWestMove[] = { 64, 65, 66, 67, 68, 69 };

	//키애니메이션 셋팅
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_FINN_SOUTH_MOVE", "WORLD_FINN", southMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_FINN_SOUTH_EAST_MOVE", "WORLD_FINN", southEastMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_FINN_EAST_MOVE", "WORLD_FINN", eastMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_FINN_NORTH_EAST_MOVE", "WORLD_FINN", northEastMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_FINN_NORTH_MOVE", "WORLD_FINN", northMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_FINN_NORTH_WEST_MOVE", "WORLD_FINN", northWestMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_FINN_WEST_MOVE", "WORLD_FINN", westMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_FINN_SOUTH_WEST_MOVE", "WORLD_FINN", southWestMove, 6, 6, true);
	KEYANIMANAGER->findAnimation("WORLD_FINN_EAST_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_FINN_WEST_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_FINN_SOUTH_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_FINN_NORTH_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_FINN_NORTH_EAST_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_FINN_NORTH_WEST_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_FINN_SOUTH_EAST_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_FINN_SOUTH_WEST_MOVE")->start();

	return S_OK;
}

void World::release()
{
}

void World::update()
{
	_finn->update();
}

void World::render()
{
	_finn->render(getMemDC());

	//Test용 텍스트
	//checkStatus();
}

void World::checkStatus()
{
	char status[128];
	sprintf_s(status, "_x : %0.f, _y : %0.f, cameraX : %0.f, cameraY : %0.f",
		_finn->getX(), _finn->getY(), CAMERA->GetCenterX(), CAMERA->GetCenterY());
	TextOut(getMemDC(), CAMERA->GetX(), CAMERA->GetY() + WINSIZEY - 50, status, strlen(status));
}

