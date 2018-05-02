#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
	: _timer(NULL)
{
}


timeManager::~timeManager()
{
}

HRESULT timeManager::init()
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release()
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

void timeManager::render(HDC hdc)
{
	char str[256];
	string frameRate;

	//폰트 배경색 지정
	//폰트 배경색 불투명 : OPAQUE
	//폰트 배경색 투명 : TRANSPARENT
	SetBkMode(hdc, OPAQUE);

#ifdef _DEBUG
	{
		wsprintf(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, CAMERA->GetX(), CAMERA->GetRC().bottom - 80, str, strlen(str));

		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOut(hdc, CAMERA->GetX(), CAMERA->GetRC().bottom - 60, str, strlen(str));

		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, CAMERA->GetX(), CAMERA->GetRC().bottom - 40, str, strlen(str));

        sprintf_s(str, "x : %d, y : %d", (int)CAMERA->GetX() + _ptMouse.x, (int)CAMERA->GetY() + _ptMouse.y);
        TextOut(hdc, CAMERA->GetX(), CAMERA->GetRC().bottom - 20, str, strlen(str));
	}
#else
	{
		wsprintf(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

	}
#endif
}
