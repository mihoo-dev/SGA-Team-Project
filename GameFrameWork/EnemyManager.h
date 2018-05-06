#pragma once
#include "gameNode.h"
#include "Enemy_Bear.h"
#include "Enemy_Bunny.h"
#include "Enemy_SmallZombie.h"
#include "Boss_Snake.h"

#include <vector>

#pragma comment ( linker, "/entry:WinMainCRTStartup /subsystem:console" )

class PlayerManager;

struct tagMoney
{
	image*	img;
	float	x, y;
	float	probeY;
	float	angle;
	float	power;
	float	gravity;
	int		speed;
	RECT	rc;
	BOOL	isActive;
};

class EnemyManager :	public gameNode
{
private:
	PlayerManager*	_pm;
	typedef vector<Enemy_SmallZombie*> vSmallZombie;

private:
	vSmallZombie _vSmallZombie;


private:
	Boss_Snake*		_snake;
	BOOL			_isSnakeStage;

	Enemy_Bear * _bear;
	BOOL _isBearStage;

	vector<Enemy_Bunny*> _vBunny;
	BOOL _isBunnyStage;

	image * dieImg;

	vector<tagMoney>	_vMoney;
	int					_moneyIndex;
	int					_endCount;

	// 플레이어 무적 시간
	int InvincibleCount;
	int InvincibleTime;
	bool isInvincible;

	bool isCollideWithPlayer();
	bool isPlayerDamaged();
	void checkIsDie();
public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update(string colPixelName);
	void render();

	//	vSmallZombie
	void setSmallZombie(int x, int y);

	//Boss Snake
	void SetSnake(float x, float y);

	//Bear & Bunny
	Enemy_Bear* GetBear() { return _bear; }
	vector<Enemy_Bunny*> GetBunny() { return _vBunny; }

	void SetBear(float x, float y);
	void SetBunny(float x, float y);

	void Die();

	//Make Money
	void MoveMoney(string colPixelName);
	void MakeMoney(float x, float y);

	//PM 전방선언 주소 연결
	void SetAdressPM(PlayerManager* PM) { _pm = PM; }
};

