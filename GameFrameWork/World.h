#pragma once
#include "gameNode.h"

class World_Character;

class World :	public gameNode
{
private:
	World_Character* _finn;

public:
	World();
	~World();

	HRESULT init();
	void release();
	void update();
	void render();

	void checkStatus();
};

