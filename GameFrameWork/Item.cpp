#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

HRESULT Item::init(float x, float y)
{
	_x = x;
	_y = y;

	_rc = RectMake(_x, _y, itemImage->getWidth(), itemImage->getHeight());

	return S_OK;
}

void Item::update()
{
}

void Item::release()
{
}

void Item::render()
{
	itemImage->render(getMemDC(), _x, _y);
}
