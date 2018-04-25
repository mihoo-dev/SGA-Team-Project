#pragma once
#include "gameNode.h"

class pixelCollision : public gameNode
{
private:
	image* _mountain;		//언덕 이미지
	image* _ball;			//공 이미지

	RECT _rc;
	float _x, _y;			//중점

	int _probeY;			//Y축 탐사 포인트

public:
	pixelCollision();
	~pixelCollision();

	HRESULT init();
	void release();
	void update();
	void render();
};

