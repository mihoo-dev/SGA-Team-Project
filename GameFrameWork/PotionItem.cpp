#include "stdafx.h"
#include "PotionItem.h"


PotionItem::PotionItem()
{
}


PotionItem::~PotionItem()
{
}

HRESULT PotionItem::init(float x, float y)
{

	IMAGEMANAGER->addImage("potion", "potion.bmp", 48, 59, true, RGB(255, 0, 255));
	itemImage = IMAGEMANAGER->findImage("potion");

	Item::init(x, y);

	itemName = "potion";

	healAmount = 50;
	_cost = 10;


	return S_OK;
}

void PotionItem::update()
{
	Item::update();
}

void PotionItem::release()
{
}

void PotionItem::render()
{
	Item::render();
}
