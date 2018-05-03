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
	virtual void render(float x, float y);

	const char* getName() { return itemName; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	float getX() { return _x; }
	float getY() { return _y; }
	int getCost() { return _cost; }
};

