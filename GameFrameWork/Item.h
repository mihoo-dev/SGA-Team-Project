#pragma once
#include "gameNode.h"
class Item : public gameNode
{
protected:
	const char* itemName;
	image* itemImage;
	RECT _rc;
	float _x, _y;
	bool isSoldOut;
	int _cost;

public:
	Item();
	~Item();

	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void release();
	virtual void render();

	const char* getName() { return itemName; }
};

