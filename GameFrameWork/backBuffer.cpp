#include "stdafx.h"
#include "backBuffer.h"


backBuffer::backBuffer() : _backBufferInfo(NULL)
{
}


backBuffer::~backBuffer()
{

}

HRESULT backBuffer::init(int width, int height)
{
	HDC hdc = GetDC(_hWnd);

	_backBufferInfo = new BackBuffer_Info;
	_backBufferInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역 생성
	_backBufferInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //빈 비트맵 이미지
	_backBufferInfo->hOBit = (HBITMAP)SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hBit);
	_backBufferInfo->width = width;
	_backBufferInfo->height = height;

	//빈 비트맵 생성이 실패하였으면
	if (_backBufferInfo->hBit == NULL)
	{
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);


	return 0;
}

void backBuffer::release(void)	
{
	if (_backBufferInfo)
	{
		SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hOBit);
		DeleteObject(_backBufferInfo->hBit);
		DeleteDC(_backBufferInfo->hMemDC);

		delete _backBufferInfo;
		_backBufferInfo = 0;
	}
}

void backBuffer::render(HDC hdc)
{
	//백DC에 그려지는 것들을 앞DC에 고속복사 해주는 함쑤
	BitBlt(hdc, 
		0, 0,					//복사되서 그려지는 곳
		_backBufferInfo->width, //복사해줄 가로크기
		_backBufferInfo->height,//복사해줄 세로크기
		_backBufferInfo->hMemDC,//복사해올 DC영역
		0,						//복사해올 좌표 X, Y
		0, 
		SRCCOPY);
}
