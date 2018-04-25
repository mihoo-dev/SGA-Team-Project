#include "stdafx.h"
#include "pixelCollision.h"


pixelCollision::pixelCollision()
{
}


pixelCollision::~pixelCollision()
{

}

HRESULT pixelCollision::init()
{
	IMAGEMANAGER->addImage("언덕", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_ball = IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2 - 100;
	_y = WINSIZEY / 2 + 110;

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//탐사축의 지점은? 공의 아래쪽
	_probeY = _y + _ball->getHeight() / 2;


	return S_OK;
}

void pixelCollision::release()
{

}

void pixelCollision::update() 
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 3.0f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 3.0f;

	//탐사축도 항상 업댓 해준다
	_probeY = _y + (_ball->getWidth() / 2);

	for (int i = _probeY - 50; i < _probeY + 50; ++i)
	{
		//픽셀값을 읽어드린다
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("언덕")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

}

void pixelCollision::render() 
{
	IMAGEMANAGER->findImage("언덕")->render(getMemDC());

	_ball->render(getMemDC(), _rc.left, _rc.top);
}
