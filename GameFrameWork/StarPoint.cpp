#include "stdafx.h"
#include "StarPoint.h"


StarPoint::StarPoint()
{
}


StarPoint::~StarPoint()
{
}

HRESULT StarPoint::init(float x, float y)
{
	IMAGEMANAGER->addImage("star", "star.bmp", 60, 60, true, RGB(255, 0, 255));
	itemImage = IMAGEMANAGER->findImage("star");

	Item::init(x, y);

	itemName = "star";
	_cost = 10;

	return S_OK;
}

void StarPoint::update()
{
}

void StarPoint::release()
{
}

void StarPoint::render()
{
	Item::render();
}
