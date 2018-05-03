#pragma once
#include "gameNode.h"
class PurchaseBtn : public gameNode
{
private:
	image* _btnImage;
	RECT _rc;

	float _x, _y;
	bool _isActive;
	bool _isClicked;

	int _frameX, _frameY;
	int _speechCnt;
	int _btnCnt;

	char* itemName;


public:
	PurchaseBtn();
	~PurchaseBtn();

	HRESULT init(float x, float y);
	void update();
	void release();
	void render(float x, float y);

	void setX(float x) { _x = x; }
	float getX() { return _x; }
	bool getIsClicked() { return _isClicked; }
	void setBool(bool isActive) { _isActive = isActive; }
};

