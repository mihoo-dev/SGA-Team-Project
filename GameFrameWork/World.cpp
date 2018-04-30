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
	IMAGEMANAGER->addFrameImage("WORLD_JAKE", "WORLD_JAKE.bmp", 512, 576, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WORLD_BRIDGE", "WORLD_BRIDGE.bmp", 1024, 260, 16, 2, true, RGB(255, 0, 255));

	_finn = new World_Character;
	_finn->init();

	_bridge = new World_Bridge;

	//전방 선언을 위한 주소 입력
	_finn->GetAdressBridge(_bridge);
	_bridge->GetAdressFinn(_finn);

	CAMERA->SetPos(_finn->GetX(), _finn->GetY());

	//각 방향 움직임 애니메이션 프레임 배열
	int southMove[]		= { 8, 9, 10, 11, 12, 13 };
	int southEastMove[] = { 16, 17, 18, 19, 20, 21 };
	int eastMove[]		= { 24, 25, 26, 27, 28, 29 };
	int northEastMove[] = { 32, 33, 34, 35, 37, 37 };
	int northMove[]		= { 40, 41, 42, 43, 44, 45 };
	int northWestMove[] = { 48, 49, 50, 51, 52, 53 };
	int westMove[]		= { 56, 57, 58, 59, 60, 61 };
	int southWestMove[] = { 64, 65, 66, 67, 68, 69 };

	//FINN 키애니메이션 셋팅
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

	//JAKE 키애니메이션 셋팅
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_JAKE_SOUTH_MOVE", "WORLD_JAKE", southMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_JAKE_SOUTH_EAST_MOVE", "WORLD_JAKE", southEastMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_JAKE_EAST_MOVE", "WORLD_JAKE", eastMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_JAKE_NORTH_EAST_MOVE", "WORLD_JAKE", northEastMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_JAKE_NORTH_MOVE", "WORLD_JAKE", northMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_JAKE_NORTH_WEST_MOVE", "WORLD_JAKE", northWestMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_JAKE_WEST_MOVE", "WORLD_JAKE", westMove, 6, 6, true);
	KEYANIMANAGER->addArrayFrameAnimation("WORLD_JAKE_SOUTH_WEST_MOVE", "WORLD_JAKE", southWestMove, 6, 6, true);
	KEYANIMANAGER->findAnimation("WORLD_JAKE_EAST_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_JAKE_WEST_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_JAKE_SOUTH_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_JAKE_NORTH_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_JAKE_NORTH_EAST_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_JAKE_NORTH_WEST_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_JAKE_SOUTH_EAST_MOVE")->start();
	KEYANIMANAGER->findAnimation("WORLD_JAKE_SOUTH_WEST_MOVE")->start();

	return S_OK;
}

void World::release()
{
	SAFE_DELETE(_finn);
	SAFE_DELETE(_bridge);
}

void World::update()
{
	KEYANIMANAGER->update();
	_finn->update();
	_bridge->update();
}

void World::render()
{
	_bridge->render(getMemDC());
	_finn->render(getMemDC());

	//Test용 텍스트
	CheckStatus();
}

void World::CheckStatus()
{
	char status[128];
	sprintf_s(status, "_x : %0.00f, _y : %0.00f, cameraX : %0.f, cameraY : %0.f",
		_finn->GetX(), _finn->GetY(), CAMERA->GetCenterX(), CAMERA->GetCenterY());
	TextOut(getMemDC(), CAMERA->GetX(), CAMERA->GetY() + WINSIZEY - 50, status, strlen(status));
}

