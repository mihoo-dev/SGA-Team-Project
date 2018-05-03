#include "stdafx.h"
#include "EnemyManager.h"
#include "PlayerManager.h"


EnemyManager::EnemyManager()
	:_isSnakeStage(false)
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init()
{
	IMAGEMANAGER->addFrameImage("BOSS_SNAKE", "BOSS_SNAKE.bmp", 3828, 3000, 11, 12, true, RGB(255, 0, 255));

	setSmallZombie(WINSIZEX / 2 + 300, WINSIZEY / 2);
	setSmallZombie(WINSIZEX / 2 + 150, WINSIZEY / 2);

	return S_OK;
}

void EnemyManager::release()
{
	if (_isSnakeStage) SAFE_DELETE(_snake);
	
	for (int i = 0; i < _vSmallZombie.size(); ++i) {
		if (_vSmallZombie[i]) SAFE_DELETE(_vSmallZombie[i]);
	}
	
}

void EnemyManager::update(PlayerManager * _pm, string colPixelName)
{
	if (_isSnakeStage) _snake->update();
	
	for (int i = 0; i < _vSmallZombie.size(); ++i) {
		if (_vSmallZombie[i]->getIsDie() == true) continue;
		_vSmallZombie[i]->update(_pm->GetPlayer(), colPixelName);
	}
	
}

void EnemyManager::render()
{
	if (_isSnakeStage) _snake->render();

	for (int i = 0; i < _vSmallZombie.size(); ++i) {
		if (_vSmallZombie[i]->getIsDie() == true) continue;
		_vSmallZombie[i]->render(getMemDC());
	}
	
}

void EnemyManager::setSmallZombie(int x, int y)
{
	_vSmallZombie.push_back(new Enemy_SmallZombie);
	_vSmallZombie[_vSmallZombie.size() - 1]->init(x,y);
}

void EnemyManager::SetSnake(float x, float y)
{
	_snake = new Boss_Snake;
	_snake->init();
	_snake->Set(x, y);
	_isSnakeStage = true;
}