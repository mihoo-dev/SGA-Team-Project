#pragma once
#include "gameNode.h"

class PlayerManager;
class EnemyManager;

class GraveyardScene :	public gameNode
{
private:
	PlayerManager* _pm;
	EnemyManager* _em;

public:
	GraveyardScene();
	~GraveyardScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

