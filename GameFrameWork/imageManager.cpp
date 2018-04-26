#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{

}

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	deleteAll();
}


image* imageManager::addImage(string strKey, int width, int height)																			
{
	image* img = findImage(strKey);

	//만약에 해당 이미지가 있다면 그 이미지 반환
	if (img) return img;

	img = new image;

	if (FAILED(img->init(width, height)))
	{
        MessageBox(_hWnd, strKey.c_str(), "이미지 에러", MB_OK);

		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor, bool alpha)
{
	image* img = findImage(strKey);

	//만약에 해당 이미지가 있다면 그 이미지 반환
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor, alpha)))
	{
        MessageBox(_hWnd, strKey.c_str(), "이미지 에러", MB_OK);

		SAFE_DELETE(img);

		return NULL;
	}

	//insert 방식엔 크게 2가지가 있다
	//pair<자료형,자료형>(자료명,자료명) 자료형을 지정해서 넣어준다
	//make_pair(자료명,자료명)  알아서 형변환해서 넣어준다

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, bool alpha)
{
	image* img = findImage(strKey);

	//만약에 해당 이미지가 있다면 그 이미지 반환
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor, alpha)))
	{
        MessageBox(_hWnd, strKey.c_str(), "이미지 에러", MB_OK);

		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}


image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, bool alpha)
{
	image* img = findImage(strKey);

	//만약에 해당 이미지가 있다면 그 이미지 반환
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor, alpha)))
	{
        MessageBox(_hWnd, strKey.c_str(), "이미지 에러", MB_OK);

		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, bool alpha)
{
	image* img = findImage(strKey);

	//만약에 해당 이미지가 있다면 그 이미지 반환
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor, alpha)))
	{
        MessageBox(_hWnd, strKey.c_str(), "이미지 에러", MB_OK);

		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}


image* imageManager::findImage(string strKey)
{
	//이터레이터에 찾고자 하는 키 값 대입
	mapImageIter key = _mImageList.find(strKey);

	//찾았다면
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}


BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}


BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	
	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			//이터레이터 갱신은 촴 중요합니다
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return TRUE;
}


//이미지 렌더
void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}


//프레임 이미지 렌더
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//과제로 한 번 추가해보세요 
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = findImage(strKey);

	if (img) img->loopRender(hdc, drawArea, offSetX, offSetY);
}

