#include "stdafx.h"
#include "BossBearScene.h"


BossBearScene::BossBearScene()
	:_alpha(255),
	_isDone(false)
{
}


BossBearScene::~BossBearScene()
{
}

HRESULT BossBearScene::init()
{
	IMAGEMANAGER->addImage("BossRoom", "BossRoom.bmp", 1148, 512, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BossRoom_Pixel", "BossRoom_Pixel.bmp", 1148, 512, true, RGB(255, 0, 255));

	_pm = new PlayerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();

	_door = new Door;
	_door->init(1050, 196);

	CAMERA->SetPos(0, 0);
	CAMERA->SetSize(IMAGEMANAGER->findImage("BossRoom")->getWidth(),
		IMAGEMANAGER->findImage("BossRoom")->getHeight());

	_em->SetBear(WINSIZEX / 2, 225);

	return S_OK;
}

void BossBearScene::release()
{
	_pm->release();

	_em->release();

	_door->release();
}

void BossBearScene::update()
{
	_pm->GetPlayer()->GroundCollision("BossRoom_Pixel");
	_pm->update();

	if (!_isDone)
	{
		if (_em->GetBear()->GetHp() <= 0)
		{
			_isDone = true;
			_em->GetBear()->Die();
		}
	}
	else
	{
		_door->Collision(_pm->GetPlayer()->GetColRC());
	}
	_door->update();
	if (!_door->GetInUse())
	{
		_door->release();
	}

	_em->GetBear()->SetPlayerInfo
	(
		_pm->GetPlayer()->GetX(),
		_pm->GetPlayer()->GetY(),
		_pm->GetPlayer()->GetColRC(),
		_pm->GetPlayer()->GetHitRC()
	);
	_em->update("BossRoom_Pixel");

	FadeOut(&_alpha);
}

void BossBearScene::render()
{
	IMAGEMANAGER->findImage("Dark Forest")->render(getMemDC(),
		CAMERA->GetX() * 0.5, 0,
		0, 0,
		IMAGEMANAGER->findImage("Dark Forest")->getWidth(),
		IMAGEMANAGER->findImage("Dark Forest")->getHeight());

	IMAGEMANAGER->findImage("Tree")->render(getMemDC(),
		CAMERA->GetX() * 0.2, 0,
		0, 0,
		IMAGEMANAGER->findImage("Tree")->getWidth(),
		IMAGEMANAGER->findImage("Tree")->getHeight());

	IMAGEMANAGER->findImage("BossRoom")->render(getMemDC(),
		0, 0,
		0, 0,
		IMAGEMANAGER->findImage("BossRoom")->getWidth(),
		IMAGEMANAGER->findImage("BossRoom")->getHeight());

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		IMAGEMANAGER->findImage("BossRoom_Pixel")->render(getMemDC(),
			0, 0,
			0, 0,
			IMAGEMANAGER->findImage("BossRoom_Pixel")->getWidth(),
			IMAGEMANAGER->findImage("BossRoom_Pixel")->getHeight());
	}
	_door->render();

	_em->render();
	_pm->render();
	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);

	char str[128];
	sprintf(str, "%d", _em->GetBear()->GetHp());
	TextOut(getMemDC(), CAMERA->GetX() + 200, CAMERA->GetY() + 200, str, strlen(str));
}

