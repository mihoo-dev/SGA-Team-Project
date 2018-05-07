#include "stdafx.h"
#include "Enemy_Worm.h"
#include "Player.h"

Enemy_Worm::Enemy_Worm()
	:img_Idle(nullptr),
	img_Move(nullptr),
	img_Attack(nullptr),
	img_Hit(nullptr),
	x(0), y(0),
	wSpeed(1.0f),
	wPower(0.5f),
	hp(5),
	atk(1),
	isAttack(false), isHit(false),
	FrameSpeed(6),
	CurrentFrameIndex(0), FramePerCount(0),
	Status(DEFAULT),
	count(0), phase(0)
{
}


Enemy_Worm::~Enemy_Worm()
{
}

#define ARR_SIZE(p) { sizeof(p) / sizeof(*p) }
HRESULT Enemy_Worm::init(int x, int y)
{
	img_Idle = IMAGEMANAGER->addFrameImage("ENEMY_WORM_IDLE", "ENEMY_WORM_IDLE.bmp", 840, 78, 10, 1, true, RGB(255, 0, 255));

	img_Move = IMAGEMANAGER->addFrameImage("ENEMY_WORM_MOVE", "ENEMY_WORM_MOVE.bmp", 1232, 78, 14, 1, true, RGB(255, 0, 255));

	img_Attack = IMAGEMANAGER->addFrameImage("ENEMY_WORM_ATTACK", "ENEMY_WORM_ATTACK.bmp", 3168, 78, 36, 1, true, RGB(255, 0, 255));

	img_Hit = IMAGEMANAGER->addFrameImage("ENEMY_WORM_HIT", "ENEMY_WORM_HIT.bmp", 1056, 78, 12, 1, true, RGB(255, 0, 255));

	KeyInfo IDLE_LEFT[] = { KeyInfo(9),KeyInfo(8),KeyInfo(7),KeyInfo(6),KeyInfo(5) };
	KeyInfo IDLE_RIGHT[] = { KeyInfo(0),KeyInfo(1),KeyInfo(2),KeyInfo(3),KeyInfo(4) };
	KeyInfo MOVE_LEFT[] = { KeyInfo(13),KeyInfo(12),KeyInfo(11),KeyInfo(10),KeyInfo(9),
		KeyInfo(8),KeyInfo(7) };
	KeyInfo MOVE_RIGHT[] = { KeyInfo(0),KeyInfo(1),KeyInfo(2),KeyInfo(3),KeyInfo(4),
		KeyInfo(5),KeyInfo(6) };
	KeyInfo ATTACK_LEFT[] = { KeyInfo(35), KeyInfo(34), KeyInfo(33), KeyInfo(32), KeyInfo(31), KeyInfo(30),
		KeyInfo(29), KeyInfo(28), KeyInfo(27), KeyInfo(26),  KeyInfo(25), KeyInfo(24),
		KeyInfo(23), KeyInfo(22), KeyInfo(21), KeyInfo(20),  KeyInfo(19), KeyInfo(18) };
	KeyInfo ATTACK_RIGHT[] = { KeyInfo(0), KeyInfo(1), KeyInfo(2), KeyInfo(3), KeyInfo(4), KeyInfo(5),
		KeyInfo(6), KeyInfo(7), KeyInfo(8), KeyInfo(9),  KeyInfo(10), KeyInfo(11),
		KeyInfo(12), KeyInfo(13), KeyInfo(14), KeyInfo(15),  KeyInfo(16), KeyInfo(17) };
	KeyInfo HIT_LEFT[] = { KeyInfo(11), KeyInfo(10), KeyInfo(9), KeyInfo(8), KeyInfo(7), KeyInfo(6) };
	KeyInfo HIT_RIGHT[] = { KeyInfo(0), KeyInfo(1), KeyInfo(2), KeyInfo(3), KeyInfo(4), KeyInfo(5) };

	AddAnimation(WORM_STATE::IDLE_LEFT, IDLE_LEFT, ARR_SIZE(IDLE_LEFT));
	AddAnimation(WORM_STATE::IDLE_RIGHT, IDLE_RIGHT, ARR_SIZE(IDLE_RIGHT));
	AddAnimation(WORM_STATE::MOVE_LEFT, MOVE_LEFT, ARR_SIZE(MOVE_LEFT));
	AddAnimation(WORM_STATE::MOVE_RIGHT, MOVE_RIGHT, ARR_SIZE(MOVE_RIGHT));
	AddAnimation(WORM_STATE::ATTACK_LEFT, ATTACK_LEFT, ARR_SIZE(ATTACK_LEFT));
	AddAnimation(WORM_STATE::ATTACK_RIGHT, ATTACK_RIGHT, ARR_SIZE(ATTACK_RIGHT));
	AddAnimation(WORM_STATE::HIT_LEFT, HIT_LEFT, ARR_SIZE(HIT_LEFT));
	AddAnimation(WORM_STATE::HIT_RIGHT, HIT_RIGHT, ARR_SIZE(HIT_RIGHT));

	ChangeAnimationFrame(WORM_STATE::IDLE_RIGHT);

	this->x = x;
	this->y = y;

	return S_OK;
}

void Enemy_Worm::AddAnimation(WORM_STATE FrameName, KeyInfo key[], UINT ArraySize)
{
	AnimKeyFrame* Temp = new AnimKeyFrame(FrameName, key, ArraySize);

	vKeyFrame.push_back(Temp);
}

void Enemy_Worm::release(void)
{
	for (UINT i = 0; i < vKeyFrame.size(); ++i)
	{
		SAFE_DELETE(vKeyFrame[i]->Frame);
		SAFE_DELETE(vKeyFrame[i]);
	}

	vKeyFrame.clear();

}

void Enemy_Worm::update(void)
{
	if ((Status == IDLE_LEFT) || (Status == IDLE_RIGHT))
	{
		rc = RectMakeCenter(x, y, img_Idle->getFrameWidth(), img_Idle->getFrameHeight());
		hitRect = RectMakeCenter(rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2 + 20, 40, 60);
	}
	else if ((Status == MOVE_LEFT) || (Status == MOVE_RIGHT))
	{
		rc = RectMakeCenter(x, y, img_Move->getFrameWidth(), img_Move->getFrameHeight());
		hitRect = RectMakeCenter(rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2 + 20, 80, 40);
	}
	else if ((Status = ATTACK_LEFT) || (Status = ATTACK_RIGHT))
	{
		rc = RectMakeCenter(x, y, img_Attack->getFrameWidth(), img_Attack->getFrameHeight());
		hitRect = RectMakeCenter(rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2 + 20, 40, 60);
	}
	else if ((Status = HIT_LEFT) || (Status = HIT_RIGHT))
	{
		rc = RectMakeCenter(x, y, img_Hit->getFrameWidth(), img_Hit->getFrameHeight());
		hitRect = RectMakeCenter(rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2 + 20, 40, 60);
	}


	WormController();
	WormAnimationUpdate();
}

void Enemy_Worm::render(HDC mDC)
{
	if ((Status == IDLE_LEFT) || (Status == IDLE_RIGHT))
	{
		img_Idle->frameRender(mDC, rc.left, rc.top, RenderFrame.FrameX, RenderFrame.FrameY);
	}
	else if ((Status == MOVE_LEFT) || (Status == MOVE_RIGHT))
	{
		img_Move->frameRender(mDC, rc.left, rc.top, RenderFrame.FrameX, RenderFrame.FrameY);
	}
	else if ((Status = ATTACK_LEFT) || (Status = ATTACK_RIGHT))
	{
		img_Attack->frameRender(mDC, rc.left, rc.top, RenderFrame.FrameX, RenderFrame.FrameY);
	}
	else if ((Status = HIT_LEFT) || (Status = HIT_RIGHT))
	{
		img_Hit->frameRender(mDC, rc.left, rc.top, RenderFrame.FrameX, RenderFrame.FrameY);
	}

	if (KEYMANAGER->isToggleKey('L'))
	{
		Rectangle(mDC, hitRect.left, hitRect.top, hitRect.right, hitRect.bottom);
	}
	else
	{
		Rectangle(mDC, 0, 0, 0, 0);
	}
}

void Enemy_Worm::ChangeAnimationFrame(WORM_STATE value)
{
	if (Status == value) return;

	UINT i = 0;
	for (i; i < vKeyFrame.size(); ++i)
		if (vKeyFrame[i]->Name == value) break;

	CurrentFrame = (*vKeyFrame[i]);
	Status = value;
	CurrentFrameIndex = 0;
	FramePerCount = 0;
}

void Enemy_Worm::WormAnimationUpdate(void)
{
	switch (Status)
	{
	case Enemy_Worm::IDLE_LEFT: case Enemy_Worm::IDLE_RIGHT:
	case Enemy_Worm::MOVE_LEFT: case Enemy_Worm::MOVE_RIGHT: 
	case Enemy_Worm::ATTACK_LEFT: case Enemy_Worm::ATTACK_RIGHT:
	case Enemy_Worm::HIT_LEFT: case Enemy_Worm::HIT_RIGHT:
		LoopAnimation();
		break;
	}
	FramePerCount++;
}

void Enemy_Worm::LoopAnimation(UINT value)
{
	if (FramePerCount % FrameSpeed == 0)
	{
		if (CurrentFrameIndex > CurrentFrame.FrameSize) CurrentFrameIndex = value;

		RenderFrame = CurrentFrame.Frame[CurrentFrameIndex++];
		FramePerCount = 0;
	}
}


void Enemy_Worm::WormController(void)
{

	count++;
	if (count % 100 == 0)
	{
		phase++;

		if (Status == MOVE_LEFT || Status == ATTACK_LEFT)
		{
			ChangeAnimationFrame(IDLE_LEFT);
		}
		else if (Status == MOVE_RIGHT || Status == ATTACK_RIGHT)
		{
			ChangeAnimationFrame(IDLE_RIGHT);
		}

		count = 0;
	}
	if (phase == 1)
	{
		ChangeAnimationFrame(MOVE_LEFT);
		x -= wSpeed;
	}
	else if (phase == 2)
	{
		if (Status == MOVE_LEFT || Status == ATTACK_LEFT)
		{
			ChangeAnimationFrame(IDLE_LEFT);
		}
		else if (Status == MOVE_RIGHT || Status == ATTACK_RIGHT)
		{
			ChangeAnimationFrame(IDLE_RIGHT);
		}
	}
	else if (phase == 3)
	{
		ChangeAnimationFrame(MOVE_RIGHT);
		x += wSpeed;
	}
	else if (phase == 4)
	{
		if (Status == MOVE_LEFT || Status == ATTACK_LEFT)
		{
			ChangeAnimationFrame(IDLE_LEFT);
		}
		else if (Status == MOVE_RIGHT || Status == ATTACK_RIGHT)
		{
			ChangeAnimationFrame(IDLE_RIGHT);
		}
		phase = 0;
	}
}