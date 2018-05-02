#include "stdafx.h"
#include "ArmorItem.h"


ArmorItem::ArmorItem()
{
}


ArmorItem::~ArmorItem()
{

}


HRESULT ArmorItem::init(float x, float y)
{
	IMAGEMANAGER->addImage("armor", "armor.bmp", 74, 54, true, RGB(255, 0, 255));
	itemImage = IMAGEMANAGER->findImage("armor");


	Item::init(x, y);

	itemName = "armor";

	_armor = 20;
	_cost = 10;


	return S_OK;
}

void ArmorItem::update()
{
	Item::update();
}

void ArmorItem::release()
{

}

void ArmorItem::render(float x, float y)
{
	Item::render(x, y);
}
