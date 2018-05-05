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
	Object* _door;

	int _alpha;

	BOOL _isDamage;
	BOOL _isDone;

public:
	BossBearScene();
	~BossBearScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

