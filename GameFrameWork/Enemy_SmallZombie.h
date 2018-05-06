#pragma once

class Player;

//TO DO : 플레이어와 연결

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
		alertJump,
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

	HRESULT	init(int x, int y);
	void	release();
	void	update(Player * player, string pixelName);
	void	render(HDC hdc);

	// getter
	bool getHp() { return hp; }
	bool getIsDead() { return isDead; }
	int	getX() { return x; }
	int	getY() { return y; }

	RECT	getHitBox() { return hitBox; }

	//setter
	void	setIsDead(bool isDead) { this->isDead = isDead; }

private:
	states state;
	imageStates imageState;

	int	x, y;		//좌표
	int	spd;		//스피드
	int	gravity;	//중력값

	int	hp;		//체력
	int	maxHp;	//최대체력

	int	jumpPower;				//점프력
	int	knockBackPower;			//넉백파워
	int	knockBackDistance;		//넉백거리
	int	maxKnockBackDistance;	//최대 넉백거리

	bool isOnGroundLeft;	
	bool isOnGroundRight;	
	bool isOnGround;		
	bool groundIsInLeft;	
	bool groundIsInRight;	
	bool cliffIsInLeft;		
	bool cliffIsInRight;	

	bool isDead;	
	bool isHit;		

	int moveX;
	int moveY;

	image * img;
	animation * anim;

	RECT hitBox;	// == collision box
	int width;		// hitBox 넓이
	int height;		// hitBox 높이
	Directions direction;	

	int hitTime;		//연속 타격 방지
	int hitTimeLimit;

	int count;

	UINT period_idleToPatrol;
	UINT check_idleToPatrol;
	UINT jumpCount;
	UINT jumpCountLimit;
	int maxMoveDistance;
	int moveDistance;

	float distFromPlayer;

	float alertRange;

	RECT Temp; //Rect for IntersectRect
	COLORREF pixelColor; // COLERREF for PixelCollision

	

private: // 다른 객체에서 받아올 것들
	Player * player;
	float playerX;
	float playerY;
	float playerAttackPower;
	RECT playerAttackBox;
	RECT playerHitBox;


private:

	void idle_behavior();
	void patrol_behavior();
	void alert_behavior();
	void alertJump_behavior();
	void getHit_behavior();

	void GetDamage();

	void GetPlayerInfo(Player * player);
	void CollisionUpdate(string pixelName);

	void PreventFastAttack(); // 연속되는 공격 방지

private:

	void changeState(states state, imageStates imgState, string animKeyName); // 상태와 animation 변경

	
};

