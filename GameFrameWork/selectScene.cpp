#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{

}

HRESULT selectScene::init()
{
	_btnSceneChange = new button;
	_btnSceneChange->init("¹öÆ°", WINSIZEX / 2, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbSceneChange);

	_action = new action;
	_action->init();

	_actionImage = IMAGEMANAGER->findImage("ÃÑ¾Ë");
	_actionImage->setX(WINSIZEX / 2);
	_actionImage->setY(WINSIZEY / 2);

	_action->moveTo(_actionImage, 50, 50, 15.0f);

	return S_OK;
}

void selectScene::release()
{
	SAFE_DELETE(_btnSceneChange);
}

void selectScene::update() 
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		
	}
	_btnSceneChange->update();
	_action->update();
}

void selectScene::render() 
{
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2 - 200, "¼¿·ºÆ®¾À", strlen("¼¿·ºÆ®¾À"));

	_btnSceneChange->render();
	_actionImage->render(getMemDC(), _actionImage->getX(), _actionImage->getY());
}

void selectScene::cbSceneChange()
{
	SCENEMANAGER->changeScene("½ºÅ¸¾À");
}