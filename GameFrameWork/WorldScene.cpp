#include "stdafx.h"
#include "WorldScene.h"
#include "World.h"

WorldScene::WorldScene()
	:_alpha(255), _sceneStart(true)
{
}


WorldScene::~WorldScene()
{
}

HRESULT WorldScene::init()
{

	_world = new World;
	_world->init(WORLDXY->GetWorldX(), WORLDXY->GetWorldY());

	CAMERA->SetSize(2793, 2111);
	CAMERA->SetPos(-(WORLDXY->GetWorldX() - WINSIZEX / 2), -(WORLDXY->GetWorldY() - WINSIZEY / 2));
	
	SOUNDMANAGER->allStop();
	SOUNDMANAGER->play("WORLDMAP", 0.5f);

	return S_OK;
}

void WorldScene::release()
{
	_world->release();
}

void WorldScene::update()
{
	_world->update();
	SceneStart();
}

void WorldScene::render()
{	//¿ùµå¸Ê ·»´õ
	IMAGEMANAGER->addImage("WORLD_MAP", "WORLD_MAP.bmp", 2793, 2111, false, NULL)->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY(), CAMERA->GetX(), CAMERA->GetY(), 600, 500);
	
	_world->render();

	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);
}

void WorldScene::SceneStart()
{
	if (_sceneStart)
	{
		FadeOut(&_alpha);
		if (_alpha == 0) _sceneStart = false;
	}
}
