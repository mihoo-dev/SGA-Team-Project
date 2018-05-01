#pragma once
#include "gameNode.h"

class Enemy_Bear : public gameNode
{
	enum STATE
	{
		LEFT_IDLE, RIGHT_IDLE,
		LEFT_WALK, RIGHT_WALK,
		LEFT_BACK, RIGHT_BACK,
		LEFT_RUN, RIGHT_RUN,
		LEFT_JUMP, RIGHT_JUMP,
		LEFT_ROAR, RIGHT_ROAR,
		LEFT_ATTACK, RIGHT_ATTACK,
		LEFT_DAMAGE, RIGHT_DAMAGE,
		LEFT_DIE, RIGHT_DIE,
		DEFAULT
	};

private:
	image * _img;
	float _x, _y;
	RECT _rc;
	STATE _state;
	float _moveSpeed;
	RECT _hitRc;

	BOOL _isRight;
	int _countTime;
	int _frameSpeed;
	int _currentFrameX;

	BOOL _isJump;
	float _jumpPower;
	float _gravity;

	int _time;

	float _playerX;
	float _playerY;
	RECT _playerRc;

public:
	Enemy_Bear();
	~Enemy_Bear();

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void draw();

	RECT GetRect() { return _rc; }

	void SetState(STATE state, UINT frameSpeed = 5);
	STATE GetState() { return _state; }

	void LoopAnimation(UINT value1 = 0);
	void OneShotAnimation(STATE state = RIGHT_IDLE);

	void SetPlayerPos(float x, float y) { _playerX = x; _playerY = y; }
	void SetPlayerRc(RECT rc) { _playerRc = rc; }
};

