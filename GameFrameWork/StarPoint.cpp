#include "stdafx.h"
#include "StarPoint.h"


StarPoint::StarPoint()
{
	_cost = 10;
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
	

	return S_OK;
}

void StarPoint::update()
{
}

void StarPoint::release()
{
}

void StarPoint::render(float x, float y)
{
	Item::render(x, y);
}
