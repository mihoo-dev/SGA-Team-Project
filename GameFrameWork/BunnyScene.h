#pragma once
#include "gameNode.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "Door.h"

class BunnyScene : public gameNode
{
private:
	PlayerManager * _pm;
	EnemyManager * _em;
	Object * _door;

	int _alpha;

	int _time;

public:
	BunnyScene();
	~BunnyScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

