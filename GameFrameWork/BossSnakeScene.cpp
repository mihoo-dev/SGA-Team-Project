#include "stdafx.h"
#include "BossSnakeScene.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

BossSnakeScene::BossSnakeScene()
{
	IMAGEMANAGER->addImage("STAGE_SNAKE", "STAGE_SNAKE.bmp", 1100, 510, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_SNAKE_PIXEL", "STAGE_SNAKE_PIXEL.bmp", 1100, 510, false, NULL);
	IMAGEMANAGER->addFrameImage("EFFECT_POISON", "EFFECT_POISON.bmp", 672, 96, 7, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("EFFECT_POISON", "EFFECT_POISON", 672, 96, 96, 96, 1, 0.2, 11);
}


BossSnakeScene::~BossSnakeScene()
{
}

HRESULT BossSnakeScene::init()
{
	CAMERA->SetSize(1100, 510);
	CAMERA->SetPos(0, 0);

	_pm = new PlayerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();
	_em->SetAdressPM(_pm);
	_em->SetSnake(CAMERA->GetX() + WINSIZEX + 300, 418 - 125);

	SOUNDMANAGER->allStop();

	_alpha = 255;
	_sceneStart = true;

	return S_OK;
}

void BossSnakeScene::release()
{

}

void BossSnakeScene::update()
{
	_pm->GetPlayer()->GroundCollision("STAGE_SNAKE_PIXEL");
	_pm->update();


	_em->update("STAGE_SNAKE_PIXEL");
}

void BossSnakeScene::render()
{
	IMAGEMANAGER->findImage("STAGE_GRAVEYARD_BACKGROUND")->render(getMemDC()
		, CAMERA->GetX(), CAMERA->GetY()
		, CAMERA->GetX(), CAMERA->GetY()
		, WINSIZEX, WINSIZEY);

	IMAGEMANAGER->findImage("STAGE_SNAKE")->render(getMemDC()
		, CAMERA->GetX(), CAMERA->GetY()
		, CAMERA->GetX(), CAMERA->GetY()
		, WINSIZEX, WINSIZEY);

	_em->render();
	_pm->render();

	EFFECTMANAGER->render();
}

void BossSnakeScene::SceneStart()
{
	if (_sceneStart)
	{
		FadeOut(&_alpha);
		if (_alpha == 0) _sceneStart = false;
	}
}

