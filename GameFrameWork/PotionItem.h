#pragma once
#include "Item.h"

class PotionItem : public Item
{
private:
	float healAmount;
	bool isActive;

public:
	PotionItem();
	~PotionItem();

	HRESULT init(float x, float y);
	void update();
	void release();
	void render(float x, float y);
};

