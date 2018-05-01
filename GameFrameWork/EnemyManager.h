#pragma once
#include "gameNode.h"
#include <vector>

class EnemyManager :	public gameNode
{
private:
public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();
};

