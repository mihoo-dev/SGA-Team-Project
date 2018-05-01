#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

image::image()
	:	_imageInfo(NULL), 
		_fileName(NULL), 
		_trans(false), 
		_transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{

	//이미지 정보가 남아있다면 해제한다
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //빈 비트맵 이미지
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//알파블렌드 셋팅
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//비트맵이 생성이 되지않았다면
	if (_imageInfo->hBit == NULL)
	{
		//해제시키고
		release();
		//초기화 실패 출력해줘라
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//파일로부터 초기화    파일명, 파일가로크기, 파일세로크기, 제외칼라
HRESULT image::init(const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor, bool alpha)
{
	//이미지 정보가 남아있다면 해제한다
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 길이를 얻어온다
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

    if (alpha)
    {
        //알파블렌드 셋팅
        _blendFunc.BlendFlags = 0;
        _blendFunc.AlphaFormat = 0;
        _blendFunc.BlendOp = AC_SRC_OVER;

        _blendImage = new IMAGE_INFO;
        _blendImage->loadType = LOAD_EMPTY;
        _blendImage->hMemDC = CreateCompatibleDC(hdc);
        _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
        _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
        _blendImage->width = WINSIZEX;
        _blendImage->height = WINSIZEY;
    }
	//비트맵이 생성이 되지않았다면
	if (_imageInfo->hBit == NULL)
	{
		//해제시키고
		release();
		//초기화 실패 출력해줘라
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y,
	int width, int height, BOOL trans, COLORREF transColor, bool alpha)
{
	//이미지 정보가 남아있다면 해제한다
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x		= x;
	_imageInfo->y		= y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 길이를 얻어온다
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

    if (alpha)
    {
        //알파블렌드 셋팅
        _blendFunc.BlendFlags = 0;
        _blendFunc.AlphaFormat = 0;
        _blendFunc.BlendOp = AC_SRC_OVER;

        _blendImage = new IMAGE_INFO;
        _blendImage->loadType = LOAD_EMPTY;
        _blendImage->hMemDC = CreateCompatibleDC(hdc);
        _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
        _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
        _blendImage->width = WINSIZEX;
        _blendImage->height = WINSIZEY;
    }
	//비트맵이 생성이 되지않았다면
	if (_imageInfo->hBit == NULL)
	{
		//해제시키고
		release();
		//초기화 실패 출력해줘라
		return E_FAIL;
	}


	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//이미지 초기화(이미지 이름, 출력좌표, 가로크기, 프레임 몇장인지)
HRESULT image::init(const char* fileName, float x, float y,
	int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool alpha)
{
	//이미지 정보가 남아있다면 해제한다
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//파일 길이를 얻어온다
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

    if (alpha)
    {
        //알파블렌드 셋팅
        _blendFunc.BlendFlags = 0;
        _blendFunc.AlphaFormat = 0;
        _blendFunc.BlendOp = AC_SRC_OVER;

        _blendImage = new IMAGE_INFO;
        _blendImage->loadType = LOAD_EMPTY;
        _blendImage->hMemDC = CreateCompatibleDC(hdc);
        _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
        _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
        _blendImage->width = WINSIZEX;
        _blendImage->height = WINSIZEY;
    }
	//비트맵이 생성이 되지않았다면
	if (_imageInfo->hBit == NULL)
	{
		//해제시키고
		release();
		//초기화 실패 출력해줘라
		return E_FAIL;
	}


	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor, bool alpha)
{
	//이미지 정보가 남아있다면 해제한다
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//파일 길이를 얻어온다
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

    if (alpha)
    {
        //알파블렌드 셋팅
        _blendFunc.BlendFlags = 0;
        _blendFunc.AlphaFormat = 0;
        _blendFunc.BlendOp = AC_SRC_OVER;

        _blendImage = new IMAGE_INFO;
        _blendImage->loadType = LOAD_EMPTY;
        _blendImage->hMemDC = CreateCompatibleDC(hdc);
        _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
        _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
        _blendImage->width = WINSIZEX;
        _blendImage->height = WINSIZEY;
    }
	//비트맵이 생성이 되지않았다면
	if (_imageInfo->hBit == NULL)
	{
		//해제시키고
		release();
		//초기화 실패 출력해줘라
		return E_FAIL;
	}


	ReleaseDC(_hWnd, hdc);

	return S_OK;
}


//메모리 해제 함수
void image::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		_trans = false;
		_transColor = NULL;
	}

}


//날려줄 컬러가 변경이 되어야한다면 사용할 함수
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
	}
	else
	{
		BitBlt(hdc,
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}


//렌더링 함수 뿌릴DC, left, top 좌표
void image::render(HDC hdc, int destX, int destY)
{
    //if (!FrustumCull(destX, destY)) return;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//뿌려줄 DC
			destX,				//뿌려줄 위치(left)
			destY,				//뿌려줄 위치(top)
			_imageInfo->width,	//가로크기
			_imageInfo->height,	//세로크기
			_imageInfo->hMemDC,	//복사해올 DC
			0, 0,				//복사해올 left, top
			_imageInfo->width,	//복사해올 가로크기
			_imageInfo->height,	//복사해올 세로크기
			_transColor);		//제외시킬 색상
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//뿌려줄 DC
			destX,				//뿌려줄 위치(left)
			destY,				//뿌려줄 위치(top)
			sourWidth,			//가로크기
			sourHeight,			//세로크기
			_imageInfo->hMemDC,	//복사해올 DC
			sourX, sourY,		//복사해올 left, top
			sourWidth,			//복사해올 가로크기
			sourHeight,			//복사해올 세로크기
			_transColor);		//제외시킬 색상
	}
	else
	{
		BitBlt(hdc, destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
    if (!FrustumCull(destX, destY)) return;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight, 
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
    if (!FrustumCull(destX, destY)) return;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//실제 이미지에 알파블렌드를 접목시켜주는 함수
	_blendFunc.SourceConstantAlpha = alpha;

	//마젠타 색상처럼 제외시킬 색상이 있다면
	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}


void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    if (!FrustumCull(destX, destY)) return;

	//실제 이미지에 알파블렌드를 접목시켜주는 함수
	_blendFunc.SourceConstantAlpha = alpha;

	//마젠타 색상처럼 제외시킬 색상이 있다면
	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}


void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
    _blendFunc.SourceConstantAlpha = alpha;

    if (_trans)
    {
        BitBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
            hdc, destX, destY, SRCCOPY);

        GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
            _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

        AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
            _blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
    }
    else
    {
        AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
            _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
    }
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    if (!FrustumCull(destX, destY)) return;

    //실제 이미지에 알파블렌드를 접목시켜주는 함수
    _blendFunc.SourceConstantAlpha = alpha;

    //마젠타 색상처럼 제외시킬 색상이 있다면
    if (_trans)
    {
        BitBlt(_blendImage->hMemDC, 0, 0,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            hdc, destX, destY, SRCCOPY);

        GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _transColor);

        AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
    }
    else
    {
        AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
    }
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
    if (!FrustumCull(destX, destY)) return;

    //실제 이미지에 알파블렌드를 접목시켜주는 함수
    _blendFunc.SourceConstantAlpha = alpha;
    _imageInfo->currentFrameX = currentFrameX;
    _imageInfo->currentFrameY = currentFrameY;

    //마젠타 색상처럼 제외시킬 색상이 있다면
    if (_trans)
    {
        BitBlt(_blendImage->hMemDC, 0, 0,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            hdc, destX, destY, SRCCOPY);

        GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            currentFrameX * _imageInfo->frameWidth,
            currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _transColor);

        AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
    }
    else
    {
        AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            currentFrameX * _imageInfo->frameWidth,
            currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
    }
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//마이너스 값에 대한 보정
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;	//복사해올 가로크기
	int sourHeight;	//복사해올 세로크기

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	//y축부터 
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{

		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//화면밖으로 나갔으면 나간영역만큼 확보해준다
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//계산된 영역을 그려줄 위치 계산
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			//나간 영역 산출
			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;


			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
    if (!FrustumCull(destX, destY)) return;

	//프레임 위치에 맞게 이미지를 뿌려준다
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::alphaAniRender(HDC hdc, int destX, int destY, animation * ani, BYTE alpha)
{
    if (!FrustumCull(destX, destY)) return;

    //프레임 위치에 맞게 이미지를 뿌려준다
    alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}

bool image::FrustumCull(int destX, int destY)
{
    if (_imageInfo->maxFrameX > 0 || _imageInfo->maxFrameY > 0)
    {
        if (destX <= CAMERA->GetRC().right &&
            destX + _imageInfo->frameWidth >= CAMERA->GetRC().left &&
            destY <= CAMERA->GetRC().bottom &&
            destY + _imageInfo->frameHeight >= CAMERA->GetRC().top)
        {
            return true;
        }
    }
    else if (_imageInfo->maxFrameX == 0 && _imageInfo->maxFrameY == 0)
    {
        if (destX <= CAMERA->GetRC().right &&
            destX + _imageInfo->width >= CAMERA->GetRC().left &&
            destY <= CAMERA->GetRC().bottom &&
            destY + _imageInfo->height >= CAMERA->GetRC().top)
        {
            return true;
        }
    }

    return false;
}
