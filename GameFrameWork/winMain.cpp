#include "stdafx.h"
#include "playGround.h"

//====================== 전 역 변 수 ============
HINSTANCE	_hInstance;		//인스턴스 번호
HWND		_hWnd;
LPTSTR _lpszClass = TEXT("Nona Windows API");

//마우스 좌표
POINT _ptMouse;
playGround _pg;


//================ 함수 프로토 타입 선언 ============
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
//==================================================

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	//윈도우 창 정보를 먼저 초기화 (셋팅) -> 그 정보를 토대로
	//윈도우 창 형태를 만들고 -> 화면에 띄운다
	MSG			message;		//윈도우 메시지 구조체
	WNDCLASS	wndClass;		//윈도우 정보를 담는 구조체

	//인스턴스 번호 대입
	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//윈도우 정보 셋팅을 토대로 등록
	RegisterClass(&wndClass);

	//윈도우 창 생성
	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,				//윈도우 창 시작 X좌표
		WINSTARTY,				//윈도우 창 시작 Y좌표
		WINSIZEX,				//윈도우 창 가로크기
		WINSIZEY,				//윈도우 창 세로크기
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//윈도우 창을 눈에 보이게 출력해준다
	ShowWindow(_hWnd, cmdShow);

	//플레이그라운드가 초기화 실패하면 널처리~
	if (FAILED(_pg.init()))
	{
		return 0;
	}

	//GetMessage : 메시지가 실제로 들어오면 처리
	//PeekMessage : 메시지가 들어오든 안들어오든 계속 루프문은 돌고있음

	/*
	// 윈도우에서 발생하는 메시지 정보 처리 루프
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);	//키보드 입력 및 마우스 클릭 메시지를 처리 해준다
		DispatchMessage(&message);	//실제로 발생한 메시지들을 전달해주는 역할 
	}
	*/

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);	//키보드 입력 및 마우스 클릭 메시지를 처리 해준다
			DispatchMessage(&message);	//실제로 발생한 메시지들을 전달해주는 역할 
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_pg.update();
			_pg.render();
		}
	}


	_pg.release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _pg.MainProc(hWnd, iMessage, wParam, lParam);
}

//클라이언트 영역 재조정을 위한 함수
void setWindowSize(int x, int y, int width, int height)
{
	//윈도우 렉트
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//윈도우 실제영역 재조정해주는 함수
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}