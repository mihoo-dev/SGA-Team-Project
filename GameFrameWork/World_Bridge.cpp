#include "stdafx.h"
#include "World_Bridge.h"
#include "World_Character.h"


World_Bridge::World_Bridge()
	:_state(0), _frameX(0), _frameY(0), _count(0)
	,_startAni(false)
	,_img(IMAGEMANAGER->findImage("WORLD_BRIDGE"))
	,_bridgeDirection(0)
{
}


World_Bridge::~World_Bridge()
{
}

HRESULT World_Bridge::init()
{

	return S_OK;
}

void World_Bridge::release()
{
	SAFE_RELEASE(_img);
}

void World_Bridge::update()
{


	//MakeBridge();
}

void World_Bridge::render(HDC hdc)
{
	if (_finn->GetBridgeState() == JAKE_MAKE_BRIDGE
		|| _finn->GetBridgeState() == FINN_HORIZONTAL_MOVE
		|| _finn->GetBridgeState() == FINN_VERTICAL_MOVE
		|| _finn->GetBridgeState() == JAKE_REMOVE_BRIDGE)	_img->frameRender(hdc, 1977, 1484, _frameX, _frameY);
}

void World_Bridge::MakeBridge()
{
	_count++;

	if (_count > 5)
	{
		_count = 0;
		_frameX++;
	}
	if (_frameX >= 7)
	{
		_frameX = 7;
		_finn->SetBridgeState(FINN_HORIZONTAL_MOVE);
		_count = 0;
	}
}

void World_Bridge::RemoveBridge()
{
	_count++;
	if (_count > 5)
	{
		_count = 0;
		_frameX++;
	}
	if (_frameX > 15)
	{
		_finn->SetBridgeState(NOTHING_TO_DO);
		_count = 0;
	}
}
