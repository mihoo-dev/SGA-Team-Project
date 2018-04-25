#pragma once
#include "ship.h"

class battle : public ship
{
public:
	battle();
	~battle();

	HRESULT init(const char* imageName, int x, int y);
	void release();
	void update();
	void render();

	void keyControl();
};

