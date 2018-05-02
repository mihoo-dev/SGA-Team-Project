#include "stdafx.h"
#include "EnemyManager.h"



EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init()
{
	setSmallZombie(WINSIZEX / 2 + 300, WINSIZEY / 2);

	return S_OK;
}

void EnemyManager::release()
{
	
	for (int i = 0; i < _vSmallZombie.size(); ++i) {
		if (_vSmallZombie[i]) SAFE_DELETE(_vSmallZombie[i]);
	}
	
}

void EnemyManager::update()
{
	
	for (int i = 0; i < _vSmallZombie.size(); ++i) {
		_vSmallZombie[i]->update();
	}
	
}

void EnemyManager::render()
{
	
	for (int i = 0; i < _vSmallZombie.size(); ++i) {
		_vSmallZombie[i]->render(getMemDC());
	}
	
}

void EnemyManager::setSmallZombie(int x, int y)
{
	_vSmallZombie.push_back(new Enemy_SmallZombie);
	_vSmallZombie[_vSmallZombie.size() - 1]->init(x,y);
}
