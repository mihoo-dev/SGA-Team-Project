#pragma once
#include "Item.h"
class StarPoint : public Item
{
private:


public:
	StarPoint();
	~StarPoint();

	HRESULT init(float x, float y);
	void update();
	void release();
	void render(float x, float y);
};

