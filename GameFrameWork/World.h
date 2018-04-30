#pragma once
#include "gameNode.h"
#include "World_Bridge.h"

class World_Character;

class World :	public gameNode
{
private:
	World_Character*	_finn;
	World_Bridge*		_bridge;

public:
	World();
	~World();

	HRESULT init();
	void release();
	void update();
	void render();

	void CheckStatus();
};

