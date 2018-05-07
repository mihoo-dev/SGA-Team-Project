#include "stdafx.h"
#include "BossBearScene.h"


BossBearScene::BossBearScene()
	:_alpha(255),
	_isDone(false),
	_isDamage(false),
	_time(0)
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
	_em->SetAdressPM(_pm);

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
}

void BossBearScene::update()
{
	_em->GetBear()->SetPlayerInfo
	(
		_pm->GetPlayer()->GetX(),
		_pm->GetPlayer()->GetY(),
		_pm->GetPlayer()->GetColRC(),
		_pm->GetPlayer()->GetHitRC()
	);

	_pm->GetPlayer()->GroundCollision("BossRoom_Pixel");
	_pm->update();

	_em->update("BossRoom_Pixel");

	if (KEYMANAGER->isOnceKeyDown(VK_F2)) _pm->GetPlayer()->SetPlayerHit();

	if (!_isDamage)
	{
		if (!_em->GetBear()->GetIsDie())
		{
			if (!_isDamage)
			{
				RECT temp;
				if (IntersectRect(&temp, &_em->GetBear()->GetRect(), &_pm->GetPlayer()->GetHitRC()))
				{
					_isDamage = true;
					_em->GetBear()->SetHp(_em->GetBear()->GetHp() - _pm->GetPlayer()->GetInfo().atk);
				}
			}
			else
			{
				RECT temp;
				if (IntersectRect(&temp, &_em->GetBear()->GetRect(), &_pm->GetPlayer()->GetHitRC()));
				else _isDamage = false;
			}
		}
	}

	if (!_isPlayerDamage)
	{
		RECT temp;
		if (IntersectRect(&temp, &_pm->GetPlayer()->GetColRC(), &_em->GetBear()->GetHitRect()) ||
			IntersectRect(&temp, &_pm->GetPlayer()->GetColRC(), &_em->GetBear()->GetWeaponRect()))
		{
			_isPlayerDamage = true;
			_pm->GetPlayer()->SetPlayerHit();
		}
	}
	else
	{
		RECT temp;
		if (IntersectRect(&temp, &_pm->GetPlayer()->GetColRC(), &_em->GetBear()->GetHitRect()) ||
			IntersectRect(&temp, &_pm->GetPlayer()->GetColRC(), &_em->GetBear()->GetWeaponRect()));
		else
		{
			_isPlayerDamage = false;
		}
	}

	if (!_isDone)
	{
		if (_em->GetBear()->GetHp() <= 0)
		{
			_isDone = true;
			_em->GetBear()->Die();
			_time = 0;
		}
	}
	else
	{
		if (_time == 0)
			_pm->GetPlayer()->SetPlayerDance();
		_time++;
		if (_time >= 100)
		{
			_alpha++;
			FadeIn(&_alpha);
		}
		if (_time >= 400)
		{
			SCENEMANAGER->changeScene("WorldScene", "LoadingScene");
		}
	}

	
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

	_em->render();
	_pm->render();
	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);
}

void BossBearScene::GoWorldMap()
{
	if (_alpha == 255)
	{
		SCENEMANAGER->changeScene("WorldScene", "LoadingScene");
	}
}
