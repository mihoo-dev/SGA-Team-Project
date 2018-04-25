#include "stdafx.h"
#include "starcraftScene.h"
#include "battle.h"

starcraftScene::starcraftScene()
{
}


starcraftScene::~starcraftScene()
{

}

HRESULT starcraftScene::init()
{
	_battle = new battle;
	_battle->init("battle", WINSIZEX / 2, WINSIZEY / 2);

	return S_OK;
}

void starcraftScene::release()
{

}

void starcraftScene::update() 
{
	_battle->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("¼¿·ºÆ®¾À");
	}
}

void starcraftScene::render() 
{
	_battle->render();

	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2 - 250, "½ºÅ¸¾À", strlen("½ºÅ¸¾À"));
}
