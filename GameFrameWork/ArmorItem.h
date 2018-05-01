#pragma once
#include "Item.h"
class ArmorItem : public Item
{
private:
	float _armor;

public:
	ArmorItem();
	~ArmorItem();

	HRESULT init(float x, float y);
	void update();
	void release();
	void render();
};

