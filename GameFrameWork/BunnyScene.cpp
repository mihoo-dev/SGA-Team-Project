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

	_door = new Door;
	_door->init(6600, 295);

	CAMERA->SetPos(0, 0);
	CAMERA->SetSize(IMAGEMANAGER->findImage("Ground")->getWidth(),
		IMAGEMANAGER->findImage("Ground")->getHeight());

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
	_pm->GetPlayer()->GroundCollision("Ground_Pixel");
	_pm->update();

	_door->Collision(_pm->GetPlayer()->GetColRC());
	_door->update();
	if (!_door->GetInUse())
	{
		_door->release();
		SAFE_DELETE(_door);
	}
	
	if (_time >= 150)
	{
		if (_em->GetBunny().size() < 5)
		{
			_em->SetBunny(CAMERA->GetRC().right + 200, 200);
		}
		_time = 0;
	}
	_time++;

	_em->update("Ground_Pixel");
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

	FadeOut(&_alpha);
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
