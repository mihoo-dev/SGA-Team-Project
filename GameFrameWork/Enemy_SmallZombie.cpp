#include "stdafx.h"
#include "Enemy_SmallZombie.h"
#include "Player.h"

Enemy_SmallZombie::Enemy_SmallZombie()
	:state(states::idle),
	imageState(imageStates::right_idle),
	spd(2), gravity(3), isOnGround(false),
	x(0), y(0), moveX(0), moveY(0),
	width(80), height(72),
	hitBox({ x,y,x+width,y+height }),
	playerHitBox({ 0,0,0,0 }),
	direction(RIGHT),
	alertRange(15),
	maxMoveDistance(100),
	period_idleToPatrol(1000)
{
}


Enemy_SmallZombie::~Enemy_SmallZombie()
{
}


HRESULT Enemy_SmallZombie::init(int x, int y)
{
	
	//idle
	IMAGEMANAGER->addFrameImage("SmallZombie_idle", "SmallZombie_idle.bmp", 738, 140, 9, 2, true, RGB(255, 0, 255));

	int rightIdle[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_rightIdle", "SmallZombie_idle", rightIdle, 9, 5, true);

	int leftIdle[] = { 9,10,11,12,13,14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_leftIdle", "SmallZombie_idle", leftIdle, 9, 5, true);

	
	//walk
	IMAGEMANAGER->addFrameImage("SmallZombie_walk", "SmallZombie_walk.bmp", 1196, 152, 13, 2, true, RGB(255, 0, 255));

	int rightWalk[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_rightWalk", "SmallZombie_walk", rightIdle, 13, 10, true);

	int leftWalk[] = { 13,14,15,16,17,18,19,20,21,22,23,24,25 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_leftWalk", "SmallZombie_walk", leftIdle, 13, 10, true);
	
	//jump
	IMAGEMANAGER->addFrameImage("SmallZombie_jump", "SmallZombie_jump.bmp", 630, 156, 7, 2, true, RGB(255, 0, 255));

	int rightJump[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_rightJump", "SmallZombie_jump", rightJump, 7, 10, true);

	int leftJump[] = { 7,8,9,10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_leftJump", "SmallZombie_jump", leftJump, 7, 10, true);
	
	//getHit
	IMAGEMANAGER->addFrameImage("SmallZombie_getHit", "SmallZombie_getHit.bmp", 344, 164, 4, 2, true, RGB(255, 0, 255));

	int rightGetHit[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_rightGetHit", "SmallZombie_getHit", rightGetHit, 4, 10, true);

	int leftGetHit[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_leftGetHit", "SmallZombie_getHit", leftGetHit, 4, 10, true);
	

	img = IMAGEMANAGER->findImage("SmallZombie_idle");
	anim = KEYANIMANAGER->findAnimation("SZ_rightIdle");
	anim->start();

	//test
	this->x = x;
	this->y = y;

	
	
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
	
	for (int i = y; i <= hitBox.bottom + moveY; i++)
	{
		COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage(pixelName)->getMemDC(), x, i);

		if (pixelColor == RGB(255, 255, 0))
		{
			if (!isOnGround) {
				isOnGround = true;
				moveY = 0;
				y = i - (height / 2);
				if (direction == LEFT) changeState(idle, left_idle, "SZ_leftIdle");
				if (direction == RIGHT) changeState(idle, right_idle, "SZ_rightIdle");
			}
		}

		pixelColor = GetPixel(IMAGEMANAGER->findImage(pixelName)->getMemDC(), x, hitBox.bottom + moveY);

		if (pixelColor == RGB(255, 0, 255))
		{
			if(isOnGround) isOnGround = false;
		}
		
	}
}

//void Enemy_SmallZombie::update(Player * player)
void Enemy_SmallZombie::update()
{
	//PlayerInfoUpdate(player);

	stateTrigger();

	if (state == states::idle) idle_behavior();
	else if (state == states::patrol) patrol_behavior();
	else if (state == states::alert) alert_behavior();

	CollisionUpdate("STAGE_GRAVEYARD_PIXEL");

	x += moveX;
	y += moveY;

	hitBox = RectMakeCenter(x, y, width, height); // update hitBox
}

void Enemy_SmallZombie::render(HDC hdc)
{
	//Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);

	img->aniRender(hdc, x - (width / 2), y - (height / 2), anim);
}


void Enemy_SmallZombie::idle_behavior()
{
	moveX = 0;
	moveY = isOnGround ? 0 : gravity;



}

void Enemy_SmallZombie::patrol_behavior()
{
	moveX = (direction == LEFT) ? -spd : spd;
	moveY = isOnGround ? 0 : gravity;

	moveDistance += moveX;

	if (abs(moveDistance) >= maxMoveDistance) {
		moveDistance = 0;
		direction = (direction == LEFT) ? RIGHT : LEFT;
		//changeState
	}

}

void Enemy_SmallZombie::alert_behavior()
{
	moveX = (x > playerX) ? -spd : spd;
	moveY = isOnGround ? 0 : gravity;

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

	moveY = isOnGround ? 0 : gravity;
}

void Enemy_SmallZombie::stateTrigger()
{
	//RECT temp;
	//if (IntersectRect(&temp, &hitBox, &player->attackBox)) state = states::getHit;

	float distFromPlayer = getDistance(x, y, playerX, playerY);

	if (state == states::idle) 
	{
		if (distFromPlayer < alertRange) state = states::alert;

		UINT i = 0;
		for (i; i <= period_idleToPatrol; ++i) {
			if (i == period_idleToPatrol) {
				bool change = RND->getFromIntTo(0, 2);
				Directions dir = (Directions)RND->getFromIntTo(0, 2);
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