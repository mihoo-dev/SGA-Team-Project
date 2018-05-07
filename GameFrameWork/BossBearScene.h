#pragma once
#include "gameNode.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "Door.h"

class BossBearScene : public gameNode
{
private:
	PlayerManager* _pm;
	EnemyManager* _em;

	int _alpha;

	BOOL _isPlayerDamage;
	BOOL _isDamage;
	BOOL _isDone;

	int _time;

public:
	BossBearScene();
	~BossBearScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void GoWorldMap();
};

