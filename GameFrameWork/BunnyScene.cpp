#include "stdafx.h"
#include "BunnyScene.h"


BunnyScene::BunnyScene()
	:_alpha(255),
	_time(0)
{
}


BunnyScene::~BunnyScene()
{
}


HRESULT BunnyScene::init()
{
	
	IMAGEMANAGER->addImage("Ground", "Ground.bmp", 0, 0, 6656, 512, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ground_Pixel", "Ground_Pixel.bmp", 0, 0, 6656, 512, true, RGB(255, 0, 255));

	_pm = new PlayerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();
	_em->SetAdressPM(_pm);

	_door = new Door;
	_door->init(6600, 295);

	CAMERA->SetPos(0, 0);
	CAMERA->SetSize(IMAGEMANAGER->findImage("Ground")->getWidth(),
		IMAGEMANAGER->findImage("Ground")->getHeight());

	_alpha = 255;
	_sceneStart = true;
	_sceneChange = false;

	return S_OK;
}

void BunnyScene::release()
{
	_pm->release();

	_em->release();

	_door->release();
}

void BunnyScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) _pm->GetPlayer()->SetPlayerHit();

	for (int i = 0; i < _em->GetBunny().size(); ++i)
	{
		if (!_em->GetBunny()[i]->GetIsDamage())
		{
			RECT temp;
			if (IntersectRect(&temp, &_em->GetBunny()[i]->GetRect(), &_pm->GetPlayer()->GetHitRC()))
			{
				_em->GetBunny()[i]->SetIsDamage(true);
				_em->GetBunny()[i]->SetHp(_em->GetBunny()[i]->GetHp() - _pm->GetPlayer()->GetInfo().atk);
			}
		}
		else
		{
			RECT temp;
			if (IntersectRect(&temp, &_em->GetBunny()[i]->GetRect(), &_pm->GetPlayer()->GetHitRC()));
			else _em->GetBunny()[i]->SetIsDamage(false);
		}

		if (!_em->GetBunny()[i]->GetIsPlayerDamage())
		{
			RECT temp;
			if (IntersectRect(&temp, &_pm->GetPlayer()->GetColRC(), &_em->GetBunny()[i]->GetHitRect()))
			{
				_em->GetBunny()[i]->SetIsPlayerDamage(true);
				_pm->GetPlayer()->SetPlayerHit();
			}
		}
		else
		{
			RECT temp;
			if (IntersectRect(&temp, &_pm->GetPlayer()->GetColRC(), &_em->GetBunny()[i]->GetHitRect()));
			else
			{
				_em->GetBunny()[i]->SetIsPlayerDamage(false);
			}
		}
	}

	if (_time >= 150)
	{
		if (_em->GetBunny().size() < 3)
		{
			_em->SetBunny(CAMERA->GetRC().right + 200, 200);
		}
		_time = 0;
	}
	_time++;


	for (int i = 0; i < _em->GetBunny().size(); ++i)
	{
		_em->GetBunny()[i]->SetPlayerInfo
		(
			_pm->GetPlayer()->GetX(),
			_pm->GetPlayer()->GetY(),
			_pm->GetPlayer()->GetColRC(),
			_pm->GetPlayer()->GetHitRC()
		);
	}

	SceneStart();

	_door->update();
	_door->Collision(_pm->GetPlayer());

	DoorEnter();

	_pm->GetPlayer()->GroundCollision("Ground_Pixel");
	_pm->update();

	_em->update("Ground_Pixel");


	GoBearStage();


	//FadeOut(&_alpha);
}

void BunnyScene::render()
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

	IMAGEMANAGER->findImage("Ground")->render(getMemDC(),
		0, 0,
		0, 0,
		IMAGEMANAGER->findImage("Ground")->getWidth(),
		IMAGEMANAGER->findImage("Ground")->getHeight());

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		IMAGEMANAGER->findImage("Ground_Pixel")->render(getMemDC(),
			0, 0,
			0, 0,
			IMAGEMANAGER->findImage("Ground_Pixel")->getWidth(),
			IMAGEMANAGER->findImage("Ground_Pixel")->getHeight());
	}
	_door->render();

	_em->render();
	_pm->render();
	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);
}


void BunnyScene::CheckStatus()
{
	char status[128];
	sprintf_s(status, "x : %0.f , y : %0.f", _pm->GetPlayer()->GetX(), _pm->GetPlayer()->GetY());
	TextOut(getMemDC(), CAMERA->GetX(), CAMERA->GetY() - 200, status, strlen(status));
}

void BunnyScene::SceneStart()
{
	if (_sceneStart)
	{
		FadeOut(&_alpha);
		if (_alpha == 0) _sceneStart = false;
	}
}

void BunnyScene::DoorEnter()
{
	if (_pm->GetPlayer()->GetX() > 6600 && !_sceneChange)
	{
		_sceneChange = true;
		_pm->GetPlayer()->ChangeAnim(Player::RIGHT_DOOR_ENTER, "PlayerRightDoorEnter");
	}

	if (_sceneChange)
		FadeIn(&_alpha);
}

void BunnyScene::GoBearStage()
{
	if (!_sceneStart && _alpha == 255)
	{
		SCENEMANAGER->changeScene("BearScene", "LoadingScene");
	}
}
