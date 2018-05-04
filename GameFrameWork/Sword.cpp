#include "stdafx.h"
#include "Sword.h"


Sword::Sword()
{
}


Sword::~Sword()
{
}

HRESULT Sword::init(float x, float y)
{
	IMAGEMANAGER->addImage("sword", "sword.bmp", 60, 60, true, RGB(255, 0, 255));
	itemImage = IMAGEMANAGER->findImage("sword");

	Item::init(x, y);

	itemName = "sword";

	atk = 10;
	
	_cost = 1000;

	return S_OK;
}

void Sword::update()
{
}

void Sword::release()
{
}

void Sword::render(float x, float y)
{
	Item::render(x, y);
}
