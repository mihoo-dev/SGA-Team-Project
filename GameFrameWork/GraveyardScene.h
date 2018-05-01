#pragma once
#include "gameNode.h"

class PlayerManager;

class GraveyardScene :	public gameNode
{
private:
	PlayerManager* _pm;

public:
	GraveyardScene();
	~GraveyardScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

