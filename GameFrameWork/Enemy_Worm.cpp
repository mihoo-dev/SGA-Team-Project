#include "stdafx.h"
#include "Enemy_Worm.h"


Enemy_Worm::Enemy_Worm()
	:img_Idle(nullptr),
	img_Move(nullptr),
	img_Attack(nullptr),
	img_Hit(nullptr),
	x(WINSIZEX / 2), y(WINSIZEY / 2),
	wSpeed(1.0f),
	wPower(0.5f),
	FrameSpeed(6),
	CurrentFrameIndex(0), FramePerCount(0),
	Status(DEFAULT)
{
}


Enemy_Worm::~Enemy_Worm()
{
}

#define ARR_SIZE(p) { sizeof(p) / sizeof(*p) }
HRESULT Enemy_Worm::init(void)
{
	img_Idle = IMAGEMANAGER->findImage("ENEMY_WORM_IDLE");
	img_Move = IMAGEMANAGER->findImage("ENEMY_WORM_MOVE");
	//img_Attack = IMAGEMANAGER->findImage("ENEMY_WORM_ATTACK");
	//img_Hit = IMAGEMANAGER->findImage("ENEMY_WORM_HIT");

	KeyInfo IDLE_LEFT[] = { KeyInfo(9),KeyInfo(8),KeyInfo(7),KeyInfo(6),KeyInfo(5) };
	KeyInfo IDLE_RIGHT[] = { KeyInfo(0),KeyInfo(1),KeyInfo(2),KeyInfo(3),KeyInfo(4) };
	KeyInfo MOVE_LEFT[] = { KeyInfo(13),KeyInfo(12),KeyInfo(11),KeyInfo(10),KeyInfo(9),
		KeyInfo(8),KeyInfo(7) };
	KeyInfo MOVE_RIGHT[] = { KeyInfo(0),KeyInfo(1),KeyInfo(2),KeyInfo(3),KeyInfo(4),
		KeyInfo(5),KeyInfo(6) };
	//KeyInfo ATTACK_LEFT[] = { KeyInfo(9),KeyInfo(8),KeyInfo(7),KeyInfo(6),KeyInfo(5) };
	//KeyInfo ATTACK_RIGHT[] = { KeyInfo(0),KeyInfo(1),KeyInfo(2),KeyInfo(3),KeyInfo(4) };
	//KeyInfo HIT_LEFT[] = { KeyInfo(9),KeyInfo(8),KeyInfo(7),KeyInfo(6),KeyInfo(5) };
	//KeyInfo HIT_RIGHT[] = { KeyInfo(0),KeyInfo(1),KeyInfo(2),KeyInfo(3),KeyInfo(4) };

	AddAnimation(WORM_STATE::IDLE_LEFT, IDLE_LEFT, ARR_SIZE(IDLE_LEFT));
	AddAnimation(WORM_STATE::IDLE_RIGHT, IDLE_RIGHT, ARR_SIZE(IDLE_RIGHT));
	AddAnimation(WORM_STATE::MOVE_LEFT, MOVE_LEFT, ARR_SIZE(MOVE_LEFT));
	AddAnimation(WORM_STATE::MOVE_RIGHT, MOVE_RIGHT, ARR_SIZE(MOVE_RIGHT));

	ChangeAnimationFrame(WORM_STATE::IDLE_RIGHT);

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


	WormAnimationUpdate();
}

void Enemy_Worm::render(HDC mDC)
{
	if ((Status == IDLE_LEFT) || (Status == IDLE_RIGHT))
	{
		img_Idle->frameRender(mDC, x, y, RenderFrame.FrameX, RenderFrame.FrameY);
	}
	else if ((Status == MOVE_LEFT) || (Status == MOVE_RIGHT))
	{
		img_Move->frameRender(mDC, x, y, RenderFrame.FrameX, RenderFrame.FrameY);
	}
	//else if ((Status = IDLE_LEFT) || (Status = IDLE_RIGHT))
	//{
	//	img_Idle->frameRender(mDC, x, y, RenderFrame.FrameX, RenderFrame.FrameY);
	//}
	//else if ((Status = IDLE_LEFT) || (Status = IDLE_RIGHT))
	//{
	//	img_Idle->frameRender(mDC, x, y, RenderFrame.FrameX, RenderFrame.FrameY);
	//}
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
	case Enemy_Worm::IDLE_LEFT:
		LoopAnimation();
		break;
	case Enemy_Worm::IDLE_RIGHT:
		LoopAnimation();
		break;
	case Enemy_Worm::MOVE_LEFT:
		LoopAnimation();
		break;
	case Enemy_Worm::MOVE_RIGHT:
		LoopAnimation();
		break;
		//case Enemy_Worm::ATTACK_LEFT:
		//	break;
		//case Enemy_Worm::ATTACK_RIGHT:
		//	break;
		//case Enemy_Worm::HIT_LEFT:
		//	break;
		//case Enemy_Worm::HIT_RIGHT:
		//	break;
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
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		ChangeAnimationFrame(MOVE_LEFT);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		ChangeAnimationFrame(MOVE_RIGHT);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		ChangeAnimationFrame(IDLE_LEFT);
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		ChangeAnimationFrame(IDLE_RIGHT);
	}
}
