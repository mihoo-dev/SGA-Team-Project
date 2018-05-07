#pragma once
#include "gameNode.h"

class Enemy_Bunny : public gameNode
{
private:
	//토끼의 상태 이넘
	enum STATE
	{
		LEFT_IDLE, RIGHT_IDLE,
		LEFT_JUMP, RIGHT_JUMP,
		DEFAULT
	};

private:
	image * _img;		//토끼 이미지
	float _x, _y;		//토끼 좌표
	RECT _rc;			//토끼 렉트
	STATE _state;		//토끼 상태 변수
	float _moveSpeed;	//토끼 점프상태에서의 이동속도
	RECT _hitRc;		//토끼 칼 렉트

	int _hp;			//토끼 HP

	BOOL _isRight;		//토끼의 방향
	int _countTime;		//프레임 이미지를 위한 카운트
	int _frameSpeed;	//프레임 속도
	int _currentFrameX;	//현재 프레임 번호
	int _currentFrameY;

	BOOL _isJump;		//점프했나
	float _jumpPower;	//점프력
	float _gravity;		//중력

	int _time;			//용도가 다양함
	int _rndTime;		//토끼가 점프하기전 대기하는 시간 랜덤
	
	float _playerX;		//플레이어 x좌표
	float _playerY;		//플레이어 y좌표
	RECT _playerRc;		//플레이어 렉트
	RECT _playerHitRc;	//플레이어 때리는 렉트
	BOOL _isDamage;
	BOOL _isPlayerDamage;

	int _probeX;
	int _probeY;

public:
	Enemy_Bunny();
	~Enemy_Bunny();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	void Move();
	void Draw();

	void Jump();

	void LoopAnimation(UINT value = 0);	//계속 루프시킴
	void OneShotAnimation();			//한번만 애니메이션
	void StopAnimation(UINT value = 0);	//그 프레임에서 멈춤

	void SetPlayerInfo(float x, float y, RECT rc, RECT hitRc) { _playerX = x; _playerY = y; _playerRc = rc; _playerHitRc = hitRc; }

	void SetState(STATE state, UINT frameSpeed = 5);
	STATE GetState() { return _state; }

	RECT GetRect() { return _rc; }

	void SetHp(int hp) { _hp = hp; }
	int GetHp() { return _hp; }

	RECT GetHitRect() { return _hitRc; }

	void PixelCollision1();
	void PixelCollision2();

	float GetX() { return _x; }
	float GetY() { return _y; }

	BOOL GetIsDamage() { return _isDamage; }
	void SetIsDamage(BOOL isDamage) { _isDamage = isDamage; }
	BOOL GetIsPlayerDamage() { return _isPlayerDamage; }
	void SetIsPlayerDamage(BOOL isPlayerDamage) { _isPlayerDamage = isPlayerDamage; }
};

