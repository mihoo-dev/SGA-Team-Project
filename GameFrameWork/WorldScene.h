#pragma once
#include "gameNode.h"

class World;

class WorldScene : public gameNode
{
private:
	World* _world;

public:
	WorldScene();
	~WorldScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

