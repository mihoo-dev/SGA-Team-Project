#pragma once
#include "gameNode.h"

#include "Enemy_SmallZombie.h"
#include "Boss_Snake.h"

#include "PlayerManager.h"

#include <vector>

#pragma comment ( linker, "/entry:WinMainCRTStartup /subsystem:console" )

class EnemyManager :	public gameNode
{
private:
	typedef vector<Enemy_SmallZombie*> vSmallZombie;

private:
	vSmallZombie _vSmallZombie;


private:
	Boss_Snake*		_snake;
	BOOL			_isSnakeStage;

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update(PlayerManager * _pm, string colPixelName);
	void render();

	//	vSmallZombie
	void setSmallZombie(int x, int y);

	//Boss Snake
	void SetSnake(float x, float y);

};

