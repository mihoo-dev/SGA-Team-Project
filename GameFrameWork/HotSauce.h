#pragma once
#include "Item.h"
class HotSauce : public Item
{
private:


public:
	HotSauce();
	~HotSauce();

	HRESULT init(float x, float y);
	void update();
	void release();
	void render(float x, float y);
};

