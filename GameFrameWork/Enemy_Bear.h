#pragma once
#include "gameNode.h"

class Enemy_Bear : public gameNode
{
private:
	//곰의 상태 이넘
	enum STATE
	{
		LEFT_IDLE, RIGHT_IDLE,
		LEFT_WALK, RIGHT_WALK,
		LEFT_BACK, RIGHT_BACK,
		LEFT_RUN, RIGHT_RUN,
		LEFT_JUMP, RIGHT_JUMP,
		LEFT_ROAR, RIGHT_ROAR,
		LEFT_ATTACK, RIGHT_ATTACK,
		LEFT_DIE, RIGHT_DIE,
		DEFAULT
	};

private:
	image * _img;		//곰 이미지
	float _x, _y;		//곰의 좌표
	RECT _rc;			//곰 렉트
	STATE _state;		//곰 상태
	float _moveSpeed;	//곰 이동속도
	RECT _weaponRc;		//곰 무기 렉트
	RECT _hitRc;		//곰 할퀴기 렉트
	int _hitTime;

	int _hp;			//곰 HP

	BOOL _isAttack;		//공격했었는가
	int _delay;			//공격 딜레이
	float _saveX;
	float _saveY;

	float _probeX;
	float _probeY;

	BOOL _isRight;		//곰 방향
	int _countTime;		//프레임 카운트
	int _frameSpeed;	//프레임 속도
	int _currentFrameX;	//현재 프레임 번호

	BOOL _isJump;		//점프 유무
	float _jumpPower;	//점프력
	float _gravity;		//중력

	int _time;			//다용도
	int _rndTime;		//여러 대기 시간 랜덤
	int _rndPattern;	//토끼의 공격패턴 랜덤

	float _playerX;		//플레이어 x좌표
	float _playerY;		//플레이어 y좌표
	RECT _playerRc;		//플레이어 렉트
	RECT _playerHitRc;	//플레이어 때리는 렉트
	BOOL _isDie;

	BOOL _isRoar;		//특수공격

public:
	Enemy_Bear();
	~Enemy_Bear();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	void Move();
	void Draw();

	void Pattern1();
	void Pattern2();
	void Pattern3();
	void Pattern4();

	void Jump();

	void Die();

	void LoopAnimation(UINT value1 = 0);	//계속 루프
	void OneShotAnimation();				//한번만 애니

	void SetPlayerInfo(float x, float y, RECT rc, RECT hitRc) { _playerX = x; _playerY = y; _playerRc = rc; _playerHitRc = hitRc; }
	void SetState(STATE state, UINT frameSpeed = 5);
	STATE GetState() { return _state; }

	RECT GetRect() { return _rc; }

	void SetHp(int hp) { _hp = hp; }
	int GetHp() { return _hp; }

	RECT GetWeaponRect() { return _weaponRc; }
	RECT GetHitRect() { return _hitRc; }

	BOOL GetIsDie() { return _isDie; }
	void SetIsDie(BOOL isDie) { _isDie = isDie; }

	BOOL GetIsRoar() { return _isRoar; }

	float GetX() { return _x; }
	float GetY() { return _y; }
};

