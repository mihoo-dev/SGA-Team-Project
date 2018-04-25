#pragma once
#include "gameNode.h"
#include "ship.h"

class battle;

class starcraftScene : public gameNode
{
private:
	ship* _battle;

public:
	starcraftScene();
	~starcraftScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

