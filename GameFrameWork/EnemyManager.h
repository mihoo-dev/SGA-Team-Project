#pragma once
#include "gameNode.h"

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

	image * dieImg;

	vector<tagMoney>	_vMoney;
	int					_moneyIndex;
	int					_endCount;

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

	//Make Money
	void MoveMoney(string colPixelName);
	void MakeMoney(float x, float y);

	//PM 전방선언 주소 연결
	void SetAdressPM(PlayerManager* PM) { _pm = PM; }
};

