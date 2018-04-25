#pragma once

class backBuffer
{
	typedef struct tagBackBufferInfo
	{
		HDC hMemDC;			//백버퍼 DC
		HBITMAP hBit;		//빈 비트맵 이미지
		HBITMAP hOBit;		//올드 비트맵
		int width;
		int height;

		tagBackBufferInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
		}
	}BackBuffer_Info, *LPBackBuffer_Info;
private:
	LPBackBuffer_Info _backBufferInfo;

public:
	backBuffer();
	~backBuffer();

	HRESULT init(int width, int height);
	void release(void);
	void render(HDC hdc);

	//메모리DC영역에 대한 접근자
	inline HDC getMemDC() { return _backBufferInfo->hMemDC; }
};

