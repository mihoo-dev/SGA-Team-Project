#pragma once

class Player;

class Enemy_SmallZombie
{
	enum imageStates
	{
		left_idle, right_idle,
		left_walk, right_walk,
		left_jump, right_jump,
		left_getHit, right_getHit
	};

	enum states
	{
		idle,
		patrol,
		alert,
		attack,
		getHit
	};

	enum Directions
	{
		LEFT,
		RIGHT
	};

public:
	Enemy_SmallZombie();
	~Enemy_SmallZombie();

	HRESULT init();
	void release();
	void update(Player * player);
	void render();

private:
	int x, y;
	int spd;
	int gravity;

	bool isOnGround;

	int moveX;
	int moveY;

	image * img;
	animation * anim;

	RECT hitBox;
	int width;
	int height;
	Directions direction;

	float alertRange;

private: // 다른 객체에서 받아올 것들
	float playerX;
	float playerY;
	RECT playerHitBox;

private:

	states state;
	imageStates imageState;

	void idle_behavior();
	void patrol_behavior();
	void alert_behavior();
	void getHit_behavior();

	void stateTrigger();

	UINT period_idleToPatrol;
	UINT period_jump;
	int moveRange;

	void PlayerInfoUpdate(Player * player);
	void CollisionUpdate(string);

private:

	void changeState(states state, imageStates imgState, string animKeyName); // 상태와 animation 변경
};

