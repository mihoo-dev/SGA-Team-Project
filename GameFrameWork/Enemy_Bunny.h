#pragma once
#include "gameNode.h"

class Enemy_Bunny : public gameNode
{
	enum STATE
	{
		LEFT_IDLE, RIGHT_IDLE,
		LEFT_JUMP, RIGHT_JUMP,
		LEFT_ATTACK, RIGHT_ATTACK,
		DEFAULT
	};

private:
	image * _img;
	float _x, _y;
	RECT _rc;
	STATE _state;
	float _moveSpeed;
	RECT _probeRc;

	BOOL _isRight;
	int _countTime;
	int _frameSpeed;
	int _currentFrameX;

	BOOL _isJump;
	float _jumpPower;
	float _gravity;

	int _time;
	int _rndTime;

public:
	Enemy_Bunny();
	~Enemy_Bunny();

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void draw();

	RECT GetRect() { return _rc; }

	void SetState(STATE state, UINT frameSpeed = 5);
	STATE GetState() { return _state; }

	void LoopAnimation(UINT value = 0);
	void OneShotAnimation();
	void WaitAnimation(UINT value = 0);
};

