#pragma once
#include "gameNode.h"
class PurchaseBtn : public gameNode
{
private:
	image* _btnImage;
	RECT _rc;

	float _x, _y;
	bool _isActive;

	int _frameX, _frameY;

public:
	PurchaseBtn();
	~PurchaseBtn();

	HRESULT init(float x, float y);
	void update();
	void release();
	void render(float x, float y);

	void setX(float x) { _x = x; }
	void setBool(bool isActive) { _isActive = isActive; }
};

