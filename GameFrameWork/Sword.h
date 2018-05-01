#pragma once
#include "Item.h"
class Sword : public Item
{
private:
	float atk;

public:
	Sword();
	~Sword();

	HRESULT init(float x, float y);
	void update();
	void release();
	void render();
};

