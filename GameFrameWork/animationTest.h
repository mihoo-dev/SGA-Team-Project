#pragma once
#include "gameNode.h"
#include "effect.h"

class animationTest : public gameNode
{
private:
	image* _camel;

	animation* _ani1;
	animation* _ani2;
	animation* _ani3;

	effect* _effect;

public:
	animationTest();
	~animationTest();

	HRESULT init();
	void release();
	void update();
	void render();
};

