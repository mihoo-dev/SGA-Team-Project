#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", 8000, 2111);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	
public:
	//HRESULT == MS전용 
	//S_OK, E_FAIL, SUCCEDED 등을 출력창에 표시해준다
	virtual HRESULT init(void);		//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release(void);		//메모리 해제 함수
	virtual void update(void);		//업데이트(연산) 함수
	virtual void render(void);	//렌더(그려주는) 함수

	//백버퍼 접근자
	image* getBackBuffer(void) { return _backBuffer; }

	//백버퍼의 DC영역에 접근자
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

