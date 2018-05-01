#include "stdafx.h"
#include "Enemy_SmallZombie.h"
#include "Player.h"

Enemy_SmallZombie::Enemy_SmallZombie()
	:state(states::idle),
	imageState(imageStates::right_idle),
	spd(3), gravity(3), isOnGround(false),
	x(0), y(0), moveX(0), moveY(0),
	width(50), height(50),
	hitBox({ x,y,x+width,y+height }),
	playerHitBox({ 0,0,0,0 }),
	direction(RIGHT),
	alertRange(15),
	moveRange(0),	
	period_idleToPatrol(10)
{
}


Enemy_SmallZombie::~Enemy_SmallZombie()
{
}


HRESULT Enemy_SmallZombie::init()
{
	IMAGEMANAGER->addFrameImage("SmallZombie_idle", "SmallZombie_idle.bmp", 369, 70, 9, 2, true, RGB(255, 0, 255));

	int rightIdle[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_rightIdle", "SmallZombie_idle", rightIdle, 9, 10, true);

	int leftIdle[] = { 9,10,11,12,13,14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_leftIdle", "SmallZombie_idle", leftIdle, 9, 10, true);



	img = IMAGEMANAGER->findImage("SmallZombie_idle");
	anim = KEYANIMANAGER->findAnimation("SZ_rightIdle");
	anim->start();

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;

	
	
	return S_OK;
}

void Enemy_SmallZombie::release()
{
}

void Enemy_SmallZombie::PlayerInfoUpdate(Player * player)
{
	playerX = player->GetX();
	playerY = player->GetY();
	playerHitBox = player->GetHitRC();

}

void Enemy_SmallZombie::CollisionUpdate(string pixelName)
{
	
	if (!isOnGround) {
		for (int i = y; i <= hitBox.bottom + moveY; i++)
		{
			COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage(pixelName)->getMemDC(), x, i);

			if (pixelColor == RGB(255, 0, 0))
			{
				isOnGround = true;
				moveY = 0;
				if (direction == LEFT) changeState(idle, left_idle, "SZ_leftIdle");
				if (direction == RIGHT) changeState(idle, right_idle, "SZ_rightIdle");
			}
		}
	}
}

void Enemy_SmallZombie::update(Player * player)
{
	PlayerInfoUpdate(player);

	stateTrigger();

	if (state == states::idle) idle_behavior();
	else if (state == states::patrol) patrol_behavior();
	else if (state == states::alert) alert_behavior();

	CollisionUpdate("STAGE_GRAVEYARD_PIXEL");

	x += moveX;
	y += moveY;

	hitBox = RectMakeCenter(x, y, width, height); // update hitBox
}

void Enemy_SmallZombie::render()
{
}


void Enemy_SmallZombie::idle_behavior()
{
	moveX = 0;
	moveY = gravity;



}

void Enemy_SmallZombie::patrol_behavior()
{
	moveX = direction ? -spd : spd;
	moveY = gravity;


}

void Enemy_SmallZombie::alert_behavior()
{
	moveX = (x > playerX) ? -spd : spd;
	moveY = gravity;

	direction = (x > playerX) ? LEFT : RIGHT;


	for (UINT i = 0; i <= period_jump; ++i) {
		if (i == period_jump) {
			bool rnd = RND->getFromIntTo(false, true);
			if (rnd == true) {
				if (direction == LEFT) changeState(alert, left_jump, "SZ_leftJump");
				if (direction == RIGHT) changeState(alert, right_jump, "SZ_rightJump");
			}
		}
	}

}

void Enemy_SmallZombie::getHit_behavior()
{

	//moveY = gravity;
}

void Enemy_SmallZombie::stateTrigger()
{
	RECT temp;
	//if (IntersectRect(&temp, &hitBox, &player->attackBox)) state = states::getHit;

	float distFromPlayer = getDistance(x, y, playerX, playerY);

	if (state == states::idle) 
	{
		if (distFromPlayer < alertRange) state = states::alert;

		UINT i = 0;
		for (i; i <= period_idleToPatrol; ++i) {
			if (i == period_idleToPatrol) {
				bool change = RND->getFromIntTo(false, true);
				bool dir = RND->getFromIntTo(LEFT, RIGHT);
				if (change == true) {
					if (dir == LEFT) changeState(patrol, left_walk, "SZ_leftWalk");
					if (dir == RIGHT) changeState(patrol, right_walk, "SZ_rightWalk");

					break;
				}
			} // 일정 주기마다 상태 변화 idle <-> patrol 
		}

	}
	else if (state == states::patrol) 
	{
		if (distFromPlayer < alertRange) state = states::alert;



	}
	else if (state == states::alert) 
	{
		
	}
}

void Enemy_SmallZombie::changeState(states state, imageStates imgState, string animKeyName)
{
	this->state = state;
	imageState = imgState;

	switch (imageState) {
	case Enemy_SmallZombie::left_idle:
	case Enemy_SmallZombie::right_idle: img = IMAGEMANAGER->findImage("SmallZombie_idle");
		break;
	case Enemy_SmallZombie::left_walk:
	case Enemy_SmallZombie::right_walk: img = IMAGEMANAGER->findImage("SmallZombie_walk");
		break;
	case Enemy_SmallZombie::left_jump:
	case Enemy_SmallZombie::right_jump: img = IMAGEMANAGER->findImage("SmallZombie_jump");
		break;
	case Enemy_SmallZombie::left_getHit:
	case Enemy_SmallZombie::right_getHit: img = IMAGEMANAGER->findImage("SmallZombie_getHit");
		break;
	}

	anim = KEYANIMANAGER->findAnimation(animKeyName);
	anim->start();

}