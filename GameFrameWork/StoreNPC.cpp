#include "stdafx.h"
#include "StoreNPC.h"


StoreNPC::StoreNPC()
{
}


StoreNPC::~StoreNPC()
{
}

HRESULT StoreNPC::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("npc", "storeNPC.bmp", 760, 264, 6, 1, true, RGB(255, 0, 255));
	_NPCImage = IMAGEMANAGER->findImage("npc");

	_x = x;
	_y = y;

	_frameX = _frameY = 0;
	_frameUpdateTime = 10;
	_currentTime = 0;


	return S_OK;
}

void StoreNPC::update()
{
	_currentTime++;

	if (_currentTime % _frameUpdateTime == 0)
	{
		_frameX++;

		if (_frameX >= _NPCImage->getMaxFrameX())
			_frameX = 0;
	}
	
}

void StoreNPC::release()
{
}

void StoreNPC::render()
{
	_NPCImage->frameRender(getMemDC(), _x, _y, _frameX, _frameY);
}