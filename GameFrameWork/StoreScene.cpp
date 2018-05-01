#include "stdafx.h"
#include "StoreScene.h"
#include "Store.h"


StoreScene::StoreScene()
{
}


StoreScene::~StoreScene()
{
}

HRESULT StoreScene::init()
{
	IMAGEMANAGER->addImage("storeBackground", "storeBackground.bmp", 600, 500, false, RGB(255, 0, 255));

	_store = new Store;
	_store->init();

	return S_OK;
}

void StoreScene::update()
{
	_store->update();
}

void StoreScene::release()
{
	//_store->release();
}

void StoreScene::render()
{
	IMAGEMANAGER->findImage("storeBackground")->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY());

	_store->render();
}
