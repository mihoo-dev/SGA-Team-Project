#include "stdafx.h"
#include "HotDogScene.h"


HotDogScene::HotDogScene()
	:_loopX(0)
{
}


HotDogScene::~HotDogScene()
{
}

HRESULT HotDogScene::init()
{
	IMAGEMANAGER->addImage("STAGE_HOTDOG", "STAGE_HOTDOG.bmp", 674, 510, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_HOTDOG_CLOUD", "STAGE_HOTDOG_CLOUD.bmp", 1200, 510, false, NULL);
	IMAGEMANAGER->addFrameImage("NPC_HOTDOG", "NPC_HOTDOG.bmp", 728, 64, 7, 1, true, RGB(255, 0, 255));

	SOUNDMANAGER->addSound("HOTDOG", "sound\\Housie Village.mp3", true, true);
	SOUNDMANAGER->allStop();
	SOUNDMANAGER->play("HOTDOG", 0.5f);

	int hotdog[] = { 0, 1, 2, 3, 4, 5, 6 };
	KEYANIMANAGER->addArrayFrameAnimation("NPC_HOTDOG_IDLE", "NPC_HOTDOG", hotdog, 7, 7, true);
	KEYANIMANAGER->findAnimation("NPC_HOTDOG_IDLE")->start();
	return S_OK;
}

void HotDogScene::release()
{
}

void HotDogScene::update()
{
	KEYANIMANAGER->update();
	_loopX += 0.2;
}

void HotDogScene::render()
{
	RECT temp = RectMake(CAMERA->GetX(), CAMERA->GetY(), WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE_HOTDOG_CLOUD")->loopRender(getMemDC(), &temp, _loopX, 0);
	IMAGEMANAGER->findImage("STAGE_HOTDOG")->render(getMemDC()
		, CAMERA->GetX(), CAMERA->GetY()
		, CAMERA->GetX(), CAMERA->GetY()
		,WINSIZEX, WINSIZEY);

	IMAGEMANAGER->findImage("NPC_HOTDOG")->aniRender(getMemDC(), CAMERA->GetX() + 470, CAMERA->GetY() + 417, KEYANIMANAGER->findAnimation("NPC_HOTDOG_IDLE"));
}
