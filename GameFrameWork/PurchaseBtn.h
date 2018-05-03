#pragma once
#include "gameNode.h"
#include "Item.h"
class PurchaseBtn : public gameNode
{
private:
	image* _btnImage;
	RECT _rc;

	float _x, _y;
	bool _isActive;
	bool _isClicked;
	bool _isBuy;

	int _frameX, _frameY;
	int _speechCnt;
	int _btnCnt;

	

	Item* _item;


public:
	PurchaseBtn();
	~PurchaseBtn();

	HRESULT init(float x, float y, Item* item);
	void update();
	void release();
	void render(float x, float y);

	void setX(float x) { _x = x; }
	float getX() { return _x; }
	bool getIsClicked() { return _isClicked; }

	int getIsBuy() { return _isBuy; }
	void setIsBuy(bool buy) { _isBuy = buy; }

	void setBool(bool isActive) { _isActive = isActive; }
	Item* getItem() { return _item; }
};

