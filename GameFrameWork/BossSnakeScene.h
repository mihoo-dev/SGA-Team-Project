#pragma once
#include "gameNode.h"

class PlayerManager;
class EnemyManager;

class BossSnakeScene :	public gameNode
{
private:
	PlayerManager* _pm;
	EnemyManager* _em;

	//페이드 화면
	int					_alpha;
	BOOL				_sceneStart;
public:
	BossSnakeScene();
	~BossSnakeScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void SceneStart();
	void DoorEnter();
	void GoWorldStage();
};

