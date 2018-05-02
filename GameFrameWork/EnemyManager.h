#pragma once
#include "gameNode.h"

#include "PlayerManager.h"

#include "Enemy_SmallZombie.h"

#include "Boss_Snake.h"

#include <vector>


#pragma comment ( linker, "/entry:WinMainCRTStartup /subsystem:console" )



class EnemyManager :	public gameNode
{
private:
	typedef vector<Enemy_SmallZombie*> vSmallZombie;



private:
	Boss_Snake* _snake;

	vSmallZombie _vSmallZombie;

	void setSmallZombie(int x, int y);

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//	vSmallZombie
	vSmallZombie getSmallZombies() { return _vSmallZombie; }

	//Boss Snake
	void SetSnake(float x, float y);
};

