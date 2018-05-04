#include "stdafx.h"
#include "StoreScene.h"
#include "Store.h"
#include <iostream>

using namespace std;

StoreScene::StoreScene()
	:_starCost(10), _starPoint(new StarPoint)
{
	_starPoint->init(0, 0);
	
}


StoreScene::~StoreScene()
{
}

HRESULT StoreScene::init()
{
	IMAGEMANAGER->addImage("storeBackground", "storeBackground.bmp", 600, 500, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("speechBalloon", "speechBalloon.bmp", 480, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("priceTags", "priceTag.bmp", 70, 54, true, RGB(255, 0, 255));
	_speechBalloon = IMAGEMANAGER->findImage("speechBalloon");
	_priceTagImage = IMAGEMANAGER->findImage("priceTags");

	_store = new Store;
	_store->init();

	_isSpeech = true;
	_state = WELCOME;

	_speechCnt = 0;
	_coins = _store->GetPlayerManager()->GetPlayer()->GetInfo().coin;

    if (TXTDATA->txtLoad("ItemInfo.txt").size() > 0)
	    _vItem = TXTDATA->txtLoad("ItemInfo.txt");

	initBackBtn();
	return S_OK;
}

void StoreScene::update()
{
	if (_isSpeech)
	{
		_speechCnt++;
		if (_speechCnt % 400 == 0) { _isSpeech = false;  _speechCnt = 0; }
	}

	/*if (_store->getBtn(1)->getIsClicked() ||
		_store->getBtn(2)->getIsClicked() ||
		_store->getBtn(3)->getIsClicked() ||
		_store->getBtn(4)->getIsClicked())
	{
		_state = THANKS;
		_isSpeech = true;
	}*/
	checkCost(1);
	checkCost(2);
	checkCost(3);
	checkCost(4);

	if (_store->getBtn(1)->getIsBuy() && _state == THANKS)
	{
		_vItem.push_back(to_string(0));
		_store->getBtn(1)->setIsBuy(false);
	}
	else if (_store->getBtn(2)->getIsBuy() && _state == THANKS)
	{
		_vItem.push_back(to_string(1));
		_store->getBtn(2)->setIsBuy(false);
	}
	else if (_store->getBtn(3)->getIsBuy() && _state == THANKS)
	{
		_vItem.push_back(to_string(2));
		_store->getBtn(3)->setIsBuy(false);
		_starPoint->setCost(_starPoint->getCost() + 10);
		_store->getBtn(3)->getItem()->setCost(_store->getBtn(3)->getItem()->getCost() + 10);
	}
	else if (_store->getBtn(4)->getIsBuy() && _state == THANKS)
	{
		_vItem.push_back(to_string(3));
		_store->getBtn(4)->setIsBuy(false);
	}

	_store->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F12))
	{
        _store->GetPlayerManager()->GetPlayer()->SaveData();
		TXTDATA->txtSave("ItemInfo.txt", _vItem);

		SCENEMANAGER->changeScene("TutorialScene", "LoadingScene");
	}
	updateBackBtn();
}

void StoreScene::release()
{
	_store->release();
	_vItem.clear();
}

void StoreScene::render()
{
	IMAGEMANAGER->findImage("storeBackground")->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY());
	_store->render();
	if (_isSpeech)
	{
		_speechBalloon->render(getMemDC(), WINSIZEX / 2 - 250, WINSIZEY / 2 + 150);

		switch (_state)
		{
		case WELCOME:
			_store->FontFunction(255, 0, 0, "어서오세요", WINSIZEX / 2 - 200, WINSIZEY / 2 + 30);
			break;
		case THANKS:
			_store->FontFunction(255, 0, 0, "감사합니다.", WINSIZEX / 2 - 200, WINSIZEY / 2 + 20);
			break;
		case DISCARCE:
			_store->FontFunction(255, 0, 0, "코인이 부족합니다", WINSIZEX / 2 - 200, WINSIZEY / 2 + 20);
			break;
		}
	}
	_store->RenderPrice(_priceTagImage, CAMERA->GetCenterX() - 40, CAMERA->GetCenterY() - 180, _starPoint->getCost());
	renderBackBtn();
}

void StoreScene::checkCost(int i)
{
	if (i > 4) return;

	if (_store->getBtn(i)->getIsBuy())
	{
		if (_coins >= _store->getBtn(i)->getItem()->getCost())
		{
            _store->GetPlayerManager()->GetPlayer()->SetCoin(
                _coins -= _store->getBtn(i)->getItem()->getCost());
			_state = THANKS;
			_isSpeech = true;
		}
		else
		{
			_state = DISCARCE;
			_isSpeech = true;
		}
	}
}

void StoreScene::initBackBtn()
{
	IMAGEMANAGER->addImage("backBtn", "storeBackBtn.bmp", 80, 80, true, RGB(255, 0, 255));
	_backBtnImage = IMAGEMANAGER->findImage("backBtn");

	_rc = RectMake(500, 10, _backBtnImage->getWidth(), _backBtnImage->getHeight());
}

void StoreScene::updateBackBtn()
{
	bool isClicked = false;

	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			isClicked = true;
	}

	if (isClicked)
	{
		isClicked = false;
		SCENEMANAGER->changeScene("WorldScene", "LoadingScene");
	}
}

void StoreScene::renderBackBtn()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	_backBtnImage->render(getMemDC(), 500, 10);
}
