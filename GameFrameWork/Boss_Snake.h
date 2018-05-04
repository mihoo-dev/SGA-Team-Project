#pragma once
#include "gameNode.h"

class Player;

class Boss_Snake : public gameNode
{
private:
	image*					_img;				//보스 이미지
	animation*				_motion;			//보스 애니메이션
	animation*				_exMotion;			//이전 애니메이션 저장
	float					_x, _y;				//보스 좌표
	BOSS_SNAKE				_state;				//보스 상태
	BOSS_SNAKE				_exState;			//이전 상태 저장
	BOSS_SNAKE_DIRECTION	_direction;			//보스 방향
	int						_HP;
												
	RECT					_rc;				//데미지 렉트
	RECT					_attackRC;			//독가스 렉트
	int						_attack;			//공격 (0:공격 아님, 1:가스, 2:근접)
	int						_attackCount;		//공격 카운트
												
	int						_count;				//카운트
	BOOL					_isPlay;			//애니 플레이 여부
	BOOL					_isDamage;			//데미지 적용 여부
	int						_startX, _endX;		//움직임 시작점 끝점

	float					playerX, playerY;
	RECT					playerAttackBox;
	RECT					playerDamageBox;

public:
	Boss_Snake();
	~Boss_Snake();

	HRESULT init();
	void release();
	void update(Player * player);
	void render();

	void Set(float x, float y);
	void CheckState(Player * player);
	void Operation();
	void Move(string direction);
	void Die();
	RECT AttackRC(Player * player);
	RECT DamageRC();
	void GetDamage();


	void GetPlayerInfo(Player * player);
	
	BOSS_SNAKE GetState() { return _state; }
	float GetX() { return _x; }
	float GetY() { return _y; }

	void SetDamage(int damage) { _HP -= damage; }
	void PlayDamage();
};

