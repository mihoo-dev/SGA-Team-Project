#include "stdafx.h"
#include "HotSauce.h"


HotSauce::HotSauce()
{
}


HotSauce::~HotSauce()
{
}

HRESULT HotSauce::init(float x, float y)
{
	IMAGEMANAGER->addImage("hotsauce", "HotSauce.bmp", 36, 72, true, RGB(255, 0, 255));
	itemImage = IMAGEMANAGER->findImage("hotsauce");

	Item::init(x, y);

	itemName = "hotsauce";

	

	return S_OK;
}

void HotSauce::update()
{
	Item::update();
}

void HotSauce::release()
{
}

void HotSauce::render(float x, float y)
{
	Item::render(x, y);
}
