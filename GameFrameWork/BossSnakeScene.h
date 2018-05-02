#pragma once
#include "gameNode.h"

class PlayerManager;
class EnemyManager;

class BossSnakeScene :	public gameNode
{
private:
	PlayerManager* _pm;
	EnemyManager* _em;

public:
	BossSnakeScene();
	~BossSnakeScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

