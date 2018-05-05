#include "stdafx.h"
#include "EnemyManager.h"
#include "PlayerManager.h"

EnemyManager::EnemyManager()
	:_isSnakeStage(false),
	_isBearStage(false),
	_isBunnyStage(false)
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init()
{
	IMAGEMANAGER->addImage("Dark Forest", "Dark Forest.bmp", 7000, 512, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Tree", "Tree.bmp", 7000, 512, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("bunny_idle", "Knife Bunny_Idle.bmp", 376, 128, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bunny_jump", "Knife Bunny_Jump.bmp", 460, 144, 5, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("STAGE_GRAVEYARD_BACKGROUND", "image\\STAGE_GRAVEYARD_BACKGROUND.bmp", 7168, 510, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_GRAVEYARD", "image\\STAGE_GRAVEYARD.bmp", 7168, 510, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_GRAVEYARD_PIXEL", "image\\STAGE_GRAVEYARD_PIXEL.bmp", 7168, 510, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("BOSS_SNAKE", "BOSS_SNAKE.bmp", 3828, 3000, 11, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MONEY", "coin.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("EFFECT_DIE", "EFFECT_DIE.bmp", 675, 75, 9, 1, true, RGB(255, 0, 255));

	EFFECTMANAGER->addEffect("dieEffect", "EFFECT_DIE", 675, 75, 75, 75, 20, TIMEMANAGER->getElapsedTime(), 10);
	

	for (int ii = 0; ii < 20; ++ii)
	{
		tagMoney money;
		money.img = IMAGEMANAGER->findImage("MONEY");
		money.x = 0;
		money.y = 0;
		money.angle = 0;
		money.power = 0;
		money.speed = 3;
		money.gravity = 0.2f;
		money.isActive = 0;

		_vMoney.push_back(money);
	}

	_moneyIndex = 0;
	_endCount = 0;
	_bear = NULL;
	return S_OK;
}

void EnemyManager::release()
{
	if (_isSnakeStage) SAFE_DELETE(_snake);
	
	if (_vSmallZombie.size() != 0) {
		for (int i = 0; i < _vSmallZombie.size(); ++i) {
			if (_vSmallZombie[i]) SAFE_DELETE(_vSmallZombie[i]);
		}
	}

	if (_bear) SAFE_DELETE(_bear);

	for (int i = 0; i < _vBunny.size(); ++i)
	{
		if (_vBunny[i]) SAFE_DELETE(_vBunny[i]);
	}
	
}
void EnemyManager::update(string colPixelName)
{
	POPUP->update();

	//스네이크 스테이지일 경우
	if (_isSnakeStage)
	{
		//스네이크 업데이트
		_snake->update(_pm->GetPlayer());

		//스네이크 죽으면
		if (_snake->GetState() == SNAKE_LEFT_DIE || _snake->GetState() == SNAKE_RIGHT_DIE)
		{
			_endCount++;
			if (_endCount > 50 && _endCount < 250 && _endCount % 10 == 0) MakeMoney(_snake->GetX() + 50, 418 - 20);
			if (_endCount > 1000)
			{
				_endCount = 0;
				WORLDXY->SetWorldX(2520);
				WORLDXY->SetWorldY(1364);
				SCENEMANAGER->changeScene("WorldScene");
			}
		}
	}

	if (_isBearStage)
	{
		_bear->update();
	}
	else if (_isBunnyStage)
	{
		for (int i = 0; i < _vBunny.size(); ++i)
		{
			_vBunny[i]->update();
		}
	}

	MoveMoney(colPixelName);

	if (KEYMANAGER->isOnceKeyDown('N')) MakeMoney(CAMERA->GetX() + WINSIZEX / 2, CAMERA->GetY() + WINSIZEY / 2);

	if (_vSmallZombie.size() != 0) {
		for (int i = 0; i < _vSmallZombie.size(); ++i) {
			if (_vSmallZombie[i]->getIsDead() == true) continue;
			_vSmallZombie[i]->update(_pm->GetPlayer(), colPixelName);
		}
	}
	
	checkIsDie();
	EFFECTMANAGER->update();
}


void EnemyManager::render()
{
	if (_isSnakeStage) _snake->render();

	if (_vSmallZombie.size() != 0) {
		for (int i = 0; i < _vSmallZombie.size(); ++i) {
			if (_vSmallZombie[i]->getIsDead() == true) continue;
			_vSmallZombie[i]->render(getMemDC());
		}
	}

	//돈 그려주기
	for (int ii = 0; ii < _vMoney.size(); ++ii)
	{
		if (_vMoney[ii].isActive)
		{
			_vMoney[ii].img->render(getMemDC(), _vMoney[ii].x - 20, _vMoney[ii].y - 20);
		}
	}

	EFFECTMANAGER->render();
	POPUP->render(getMemDC());
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

void EnemyManager::checkIsDie()
{
	if (_vSmallZombie.size() != 0) {
		for (int i = 0; i < _vSmallZombie.size(); ++i) {
			if (_vSmallZombie[i]->getHp() <= 0 && _vSmallZombie[i]->getIsDead() == false) {
				EFFECTMANAGER->play("dieEffect",_vSmallZombie[i]->getX(), _vSmallZombie[i]->getY());
				MakeMoney(_vSmallZombie[i]->getX(), _vSmallZombie[i]->getY());
				_vSmallZombie[i]->setIsDead(true);
				break;
			}
		}
	}
}

void EnemyManager::SetBear(float x, float y)
{
	_bear = new Enemy_Bear;
	_bear->init(x, y);

	_isBearStage = true;
}

void EnemyManager::SetBunny(float x, float y)
{
	_vBunny.push_back(new Enemy_Bunny);
	_vBunny[_vBunny.size() - 1]->init(x, y);

	_isBunnyStage = true;
}


void EnemyManager::MoveMoney(string colPixelName)
{
	for (int ii = 0; ii < _vMoney.size(); ++ii)
	{
		_vMoney[ii].probeY = _vMoney[ii].y + 20;

		if (_vMoney[ii].isActive)
		{
			_vMoney[ii].x += cosf(_vMoney[ii].angle) * _vMoney[ii].speed;
			_vMoney[ii].y -= sinf(_vMoney[ii].angle) * _vMoney[ii].speed;
			_vMoney[ii].y -= _vMoney[ii].power;
			_vMoney[ii].power -= _vMoney[ii].gravity;
			COLORREF pixel = GetPixel(IMAGEMANAGER->findImage(colPixelName)->getMemDC(), _vMoney[ii].x, _vMoney[ii].probeY);

			if (pixel == RGB(0,255,255) || pixel == RGB(255,255,0))
			{
				if (_vMoney[ii].power > 0) return;
				_vMoney[ii].gravity = 0;
				_vMoney[ii].speed = 0;
				_vMoney[ii].power = 0;
			}
		}
		else
		{
			_vMoney[ii].rc = { 0,0,0,0 };
		}
	}
}

void EnemyManager::MakeMoney(float x, float y)
{
	_vMoney[_moneyIndex].x = x;
	_vMoney[_moneyIndex].y = y;
	_vMoney[_moneyIndex].isActive = true;
	_vMoney[_moneyIndex].angle = RND->getFromFloatTo(PI / 4, (PI / 4) * 3);
	_vMoney[_moneyIndex].power = RND->getFromFloatTo(0.1, 2.0);
	_vMoney[_moneyIndex].speed = 3;
	_vMoney[_moneyIndex].gravity = 0.2f;
	_moneyIndex++;
	if (_moneyIndex > _vMoney.size() - 1) _moneyIndex = 0;
}
