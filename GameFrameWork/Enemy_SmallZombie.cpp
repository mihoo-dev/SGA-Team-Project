#include "stdafx.h"
#include "Enemy_SmallZombie.h"
#include "Player.h"

Enemy_SmallZombie::Enemy_SmallZombie()
	:state(states::idle),
	imageState(imageStates::right_idle),
	maxHp(10), hp(maxHp), isDie(false),
	spd(1), gravity(4), isOnGround(false),
	groundIsInLeft(false), groundIsInRight(false),
	cliffIsInLeft(false), cliffIsInRight(false),
	jumpPower(5), knockBackPower(5),
	maxKnockBackDistance(60),
	knockBackDistance(0),
	x(0), y(0), moveX(0), moveY(0),
	width(80), height(72),
	hitBox({ x,y,x + width,y + height }),
	playerHitBox({ 0,0,0,0 }),
	direction(RIGHT),
	alertRange(15),
	maxMoveDistance(170),
	moveDistance(0),
	period_idleToPatrol(120)
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
	KEYANIMANAGER->addArrayFrameAnimation("SZ_rightWalk", "SmallZombie_walk", rightWalk, 13, 5, true);

	int leftWalk[] = { 13,14,15,16,17,18,19,20,21,22,23,24,25 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_leftWalk", "SmallZombie_walk", leftWalk, 13, 5, true);
	
	//jump
	IMAGEMANAGER->addFrameImage("SmallZombie_jump", "SmallZombie_jump.bmp", 630, 156, 7, 2, true, RGB(255, 0, 255));

	int rightJump[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_rightJump", "SmallZombie_jump", rightJump, 7, 7, true);

	int leftJump[] = { 7,8,9,10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_leftJump", "SmallZombie_jump", leftJump, 7, 7, true);
	
	//getHit
	IMAGEMANAGER->addFrameImage("SmallZombie_getHit", "SmallZombie_getHit.bmp", 344, 164, 4, 2, true, RGB(255, 0, 255));

	int rightGetHit[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_rightGetHit", "SmallZombie_getHit", rightGetHit, 4, 4, true);

	int leftGetHit[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("SZ_leftGetHit", "SmallZombie_getHit", leftGetHit, 4, 4, true);
	

	changeState(idle, right_idle, "SZ_rightIdle");

	//test
	this->x = x;
	this->y = y;

	
	
	return S_OK;
}

void Enemy_SmallZombie::release()
{
}

void Enemy_SmallZombie::GetPlayerInfo(Player * player)
{
	playerX = player->GetX();
	playerY = player->GetY();
	//playerAttackPower = player->getAttackPower();
	playerHitBox = player->GetHitRC();

}

void Enemy_SmallZombie::CollisionUpdate(string pixelName)
{

	#pragma region GroundCollision
	//Bottom
	for (int i = hitBox.top; i <= hitBox.bottom + moveY; i++)
	{
		COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage(pixelName)->getMemDC(), x, i);

		if (pixelColor == RGB(255, 255, 0))
		{
			if (!isOnGround) {
				isOnGround = true;
				moveY = 0;
				y = i - (height / 2);
			}
		}

		pixelColor = GetPixel(IMAGEMANAGER->findImage(pixelName)->getMemDC(), x, hitBox.bottom + moveY);

		if (pixelColor == RGB(255, 0, 255))
		{
			if (isOnGround) isOnGround = false;
		}
	}
	//left
	if (direction == LEFT)
	{
		for (int i = x; i >= hitBox.left + moveX; i--)
		{
			COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage(pixelName)->getMemDC(), i, hitBox.bottom - 10);

			if (pixelColor == RGB(255, 255, 0))
			{
				moveX = 0;
				groundIsInLeft = true;
			}
			if (pixelColor == RGB(255, 0, 255))
			{
				groundIsInLeft = false;
			}
		}
	}
	//right
	else if (direction == RIGHT)
	{
		for (int i = x; i <= hitBox.right + moveX; i++)
		{
			COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage(pixelName)->getMemDC(), i, hitBox.bottom - 10);

			if (pixelColor == RGB(255, 255, 0))
			{
				moveX = 0;
				groundIsInRight = true;
			}
			if (pixelColor == RGB(255, 0, 255))
			{
				groundIsInRight = false;
			}
		}
	}
	#pragma endregion

	
	#pragma region PreventCliffFall
	
	//left
	if (direction == LEFT && isOnGround)
	{
		COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage(pixelName)->getMemDC(), hitBox.left, hitBox.bottom + 5);

		if (pixelColor == RGB(0, 255, 255) && !cliffIsInLeft)
		{
			cliffIsInLeft = true;
			changeState(idle, left_idle, "SZ_leftIdle");
		}
		else if (pixelColor != RGB(0, 255, 255))
		{
			cliffIsInLeft = false;
		}
	}
	//right
	else if (direction == RIGHT && isOnGround)
	{
		
		COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage(pixelName)->getMemDC(), hitBox.right, hitBox.bottom + 5);

		if (pixelColor == RGB(0, 255, 255) && !cliffIsInRight)
		{
			cliffIsInRight = true;
			changeState(idle, right_idle, "SZ_rightIdle");
		}
		else if (pixelColor != RGB(0, 255, 255))
		{
			cliffIsInRight = false;
		}
	}
	

	#pragma endregion

	if (hitBox.left + moveX < CAMERA->GetRC().left) {   
		if (state != getHit) changeState(idle, right_idle, "SZ_rightIdle");
		moveX = 0;
	}
	else if (hitBox.right + moveX > CAMERA->GetRC().right) {
		if (state != getHit) changeState(idle, left_idle, "SZ_leftIdle");
		moveX = 0;
	}
}


//void Enemy_SmallZombie::update(Player * player, string colPixelName)
void Enemy_SmallZombie::update()
{
	CheckIsDie(hp);

	//GetPlayerInfo(player);

	distFromPlayer = getDistance(x, y, playerX, playerY);

	stateTrigger();

	switch (state)
	{
	case idle: idle_behavior();
		break;
	case patrol: patrol_behavior();
		break;
	case alert: alert_behavior();
		break;
	case alertJump: alertJump_behavior();
		break;
	case getHit: getHit_behavior();
		break;

	}

	CollisionUpdate("STAGE_GRAVEYARD_PIXEL");

	x += moveX;
	y += moveY;

	hitBox = RectMakeCenter(x, y, width, height); // update hitBox

}

void Enemy_SmallZombie::render(HDC hdc)
{
	DrawFocusRect(hdc, &hitBox); // test box

	img->aniRender(hdc, x - (width / 2), y - (height / 2), anim);
}


void Enemy_SmallZombie::idle_behavior()
{
	moveX = 0;
	moveY = isOnGround ? 0 : gravity;


	#pragma region IdleToPatrol
	check_idleToPatrol++;

	if (period_idleToPatrol <= check_idleToPatrol) {
		check_idleToPatrol = 0;
		bool change = (bool)RND->getFromIntTo(0, 3); // 33%
		direction = (Directions)RND->getFromIntTo(0, 2);
		if (change == true) {
			if (direction == LEFT && !groundIsInLeft && !cliffIsInLeft) changeState(patrol, left_walk, "SZ_leftWalk");
			if (direction == RIGHT && !groundIsInRight && !cliffIsInRight) changeState(patrol, right_walk, "SZ_rightWalk");
		}
	} // 일정 주기마다 상태 변화 idle -> patrol 
	#pragma endregion

	#pragma region IdleToAlert
	if (distFromPlayer < alertRange) state = states::alert;
#pragma endregion

}

void Enemy_SmallZombie::patrol_behavior()
{
	moveX = (direction == LEFT) ? -spd : spd;
	moveY = isOnGround ? 0 : gravity;



	#pragma region PatrolToIdle
	moveDistance += moveX;

	if (abs(moveDistance) >= maxMoveDistance) {
		moveDistance = 0;
		if (direction == LEFT) changeState(idle, left_idle, "SZ_leftIdle");
		else if (direction == RIGHT) changeState(idle, right_idle, "SZ_rightIdle");
	} // Patrole -> Idle
	#pragma endregion

	#pragma region IdleToAlert
	if (distFromPlayer < alertRange) state = states::alert;
#pragma endregion
}

void Enemy_SmallZombie::alert_behavior()
{
	moveX = (x > playerX) ? -spd : spd;
	moveY = isOnGround ? 0 : gravity;

	direction = (x > playerX) ? LEFT : RIGHT;

	#pragma region AlertToJump 
	/*
	jumpCount++;

	if (jumpCount >= jumpCountLimit) {
		jumpCount = 0;
		int rnd = RND->getFromIntTo(0, 4); // 25%
		if (rnd == true) {
			jumpPower = 5;
			if (direction == LEFT) changeState(alertJump, left_jump, "SZ_leftJump");
			if (direction == RIGHT) changeState(alertJump, right_jump, "SZ_rightJump");
		}
	} // Alert -> Jump
	*/ 
	#pragma endregion
	
	#pragma region AlertToGetHit
	/*
	if (IntersectRect(&Temp, &hitBox, &player->attackBox)) {
		hp -= playerAttackPower; // 맞으면 hp 감소
		if (x > playerX) changeState(getHit, left_getHit, "SZ_leftGetHit");
		else changeState(getHit, right_getHit, "SZ_rightGetHit");
	}
	*/
#pragma endregion


}

void Enemy_SmallZombie::alertJump_behavior()
{


}

void Enemy_SmallZombie::getHit_behavior()
{
	moveX = (x > playerX) ? knockBackPower : -knockBackPower;
	moveY = isOnGround ? 0 : gravity;

	knockBackDistance += moveX;

	if (abs(knockBackDistance) >= maxKnockBackDistance)
	{
		knockBackDistance = 0;
		(x > playerX) ? changeState(idle, right_idle, "SZ_rightIdle")
					  : changeState(idle, left_idle, "SZ_leftIdle");
	}

}

void Enemy_SmallZombie::stateTrigger()
{

	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		if (x > playerX) changeState(getHit, left_getHit, "SZ_leftGetHit");
		else changeState(getHit, right_getHit, "SZ_rightGetHit");
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

void Enemy_SmallZombie::CheckIsDie(int hp)
{
	//if (hp <= 0) isDie = true;
}
