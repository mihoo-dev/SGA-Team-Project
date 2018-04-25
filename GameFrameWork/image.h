#pragma once
#include "animation.h"
//======================================
// ## 18.02.27 ## - image Class - ##
//======================================

class image
{
public:
	//이미지가 로드되는 타입
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//리소스로부터 
		LOAD_FILE,			//파일로부터
		LOAD_EMPTY,			//빈 비트맵을 생성
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD		resID;		//리소스 불러올때 레지스터 넘버
		HDC			hMemDC;		//메모리 DC
		HBITMAP		hBit;		//비트맵
		HBITMAP		hOBit;
		float		x;			//이미지의 x좌표(left)
		float		y;			//이미지의 y좌표(top)
		int			width;
		int			height;

		int			currentFrameX;	//현재 프레임 번호 X
		int			currentFrameY;	//현재 프레임 번호 Y
		int			maxFrameX;		//최대 프레임 번호 X
		int			maxFrameY;		//최대 프레임 번호 Y
		int			frameWidth;		//프레임 가로크기
		int			frameHeight;	//프레임 세로크기
		BYTE		loadType;
		RECT		boundingBox;	//충돌체크 용 박스

		tagImageInfo()
		{
			resID			= 0;
			hMemDC			= NULL;
			hBit			= NULL;
			hOBit			= NULL;
			x				= 0;
			y				= 0;
			width			= 0;
			height			= 0;
			currentFrameX	= 0;
			currentFrameY	= 0;
			maxFrameX		= 0;
			maxFrameY		= 0;
			frameWidth		= 0;
			frameHeight		= 0;
			loadType		= LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보 구조체
	CHAR*			_fileName;		//파일로부터 로드해올때 파일 이름 저장
	BOOL			_trans;			//특정컬러를 제외시킬꺼냐
	COLORREF		_transColor;	//특정컬러 값이 무어냐

	BLENDFUNCTION	_blendFunc;		//알파블렌드 함수
	LPIMAGE_INFO	_blendImage;	//알파블렌드 이미지

public:
	image();
	~image();

	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, bool alpha = false);
	HRESULT init(const char* fileName, float x, float y,
		int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, bool alpha = false);

	//이미지 초기화(이미지 이름, 출력좌표, 가로크기, 프레임 몇장인지)
	HRESULT init(const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE, bool alpha = false);

	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE, bool alpha = false);

	//메모리 해제 함수
	void release(void);

	//날려줄 컬러가 변경이 되어야한다면 사용할 함수
	void setTransColor(BOOL trans, COLORREF transColor);

	void render(HDC hdc);
	//렌더링 함수 뿌릴DC, left, top 좌표
	void render(HDC hdc, int destX, int destY);

	//렌더링 함수 뿌릴DC, 뿌려줄X,Y, 복사해올X(left),Y(top),Width,Height
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	
    void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
    void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	
	void aniRender(HDC hdc, int destX, int destY, animation* ani);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//이미지 조작을 간편하기 위한 Getter, Setter

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	// 이미지를 중점좌표로 움직이자
	inline void setCenter(float x, float y)
	{
		//프레임이미지일떄와 그냥 단일이미지일때 조건줘서
		//분리해보시오

		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	//충돌체크용 바운딩박스
	inline RECT boundingBox()
	{
		//여러분 입맛에 맞게 짜보세요
		RECT rc = { _imageInfo->x,
					_imageInfo->y,
					_imageInfo->x + _imageInfo->frameWidth,
					_imageInfo->y + _imageInfo->frameHeight };

		return rc;
	}

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
};

