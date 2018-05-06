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
	int _time;
	int _alpha;
	BOOL _sceneStart;
	BOOL _sceneChange;

public:
	BunnyScene();
	~BunnyScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void CheckStatus();
	void SceneStart();
	void DoorEnter();
	void GoBearStage();
};

