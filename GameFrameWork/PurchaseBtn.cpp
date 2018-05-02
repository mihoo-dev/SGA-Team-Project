#include "stdafx.h"
#include "PurchaseBtn.h"


PurchaseBtn::PurchaseBtn()
{
}


PurchaseBtn::~PurchaseBtn()
{
}

HRESULT PurchaseBtn::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("btn", "BuyBtn.bmp", 137, 44, 3, 1, true, RGB(255, 0, 255));
	_btnImage = IMAGEMANAGER->findImage("btn");

	_x = x;
	_y = y;

	_isActive = false;

	_frameX = 1;
	_frameY = 0;

	_rc = RectMake(_x, _y, _btnImage->getFrameWidth(), _btnImage->getFrameHeight());


	return S_OK;
}

void PurchaseBtn::update()
{
	if (_isActive)
	{
		if (PtInRect(&_rc, _ptMouse))
		{
			_frameX = 0;
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_frameX = 2;
			}
			else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				_frameX = 0;
			}
		}
		else
		{
			_frameX = 1;
		}

	}
	else
	{
		_frameX = 1;
	}
	//_rc = RectMake(_x, _y, _btnImage->getFrameWidth(), _btnImage->getFrameHeight());
}

void PurchaseBtn::release()
{
}

void PurchaseBtn::render(float x, float y)
{
	if (_isActive)
	{
		TextOut(getMemDC(), CAMERA->GetCenterX(), CAMERA->GetCenterY(), "충돌!", strlen("충돌!"));
	}
	_btnImage->frameRender(getMemDC(), x, y, _frameX, _frameY);
}
