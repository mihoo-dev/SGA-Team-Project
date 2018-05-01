#pragma once
#include "gameNode.h"

#include "PlayerManager.h"

#include "Enemy_SmallZombie.h"

#include <vector>

class EnemyManager :	public gameNode
{
private:
	typedef vector<Enemy_SmallZombie*> vSmallZombie;



private:
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

};

