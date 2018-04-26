#include "stdafx.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
}

HRESULT CameraManager::init(const char * name)
{
    /*offSetX2 = -(((WINSIZEX / 2) * 5) - WINSIZEX / 2);
    offSetY2 = -(((WINSIZEY / 2)) - WINSIZEY / 2);*/
    offSetX2 = 0;
    offSetY2 = 0;

    _x = WINSIZEX / 2 - offSetX2;
    _y = WINSIZEY / 2 - offSetY2;

    _cameraSpeed = 0;

    _state = MOVE;

    imageName = name;

    backgroundSizeX = GAMESIZEX;
    backgroundSizeY = GAMESIZEY;

    return S_OK;
}

void CameraManager::release()
{
}

void CameraManager::update(float x, float y, float speed, bool isPlayer)
{
    //속도를 한번만 저장하기 위함
    if (!_forOnce)
    {
        _cameraSpeed = speed;
        _forOnce = true;
    }

    if (KEYMANAGER->isOnceKeyDown(VK_TAB))
    {
        if (_state == FOLLOW)
            _state = CONTROL;
        else if (_state == CONTROL)
            _state = MOVE;
    }

    if (_state == CONTROL)
    {
        if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
            _controlSpeed = 5;
        if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
            _controlSpeed = 5;
        if (KEYMANAGER->isOnceKeyDown(VK_UP))
            _controlSpeed = 5;
        if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
            _controlSpeed = 5;


        if (KEYMANAGER->isStayKeyDown(VK_LEFT))
        {
            if (offSetY2 <= 0)
                offSetX2 += _controlSpeed;
            if (offSetX2 > 0)
            {
                _controlSpeed = 0;
                offSetX2 = 0;
            }
        }
        if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
        {
            if (offSetX2 >= WINSIZEX - backgroundSizeX)
                offSetX2 -= _controlSpeed;
            if (offSetX2 < WINSIZEX - backgroundSizeX)
            {
                _controlSpeed = 0;
                offSetX2 = WINSIZEX - backgroundSizeX;
            }
        }
        if (KEYMANAGER->isStayKeyDown(VK_UP))
        {
            if (offSetY2 <= 0)
                offSetY2 += _controlSpeed;
            if (offSetY2 > 0)
            {
                _controlSpeed = 0;
                offSetY2 = 0;
            }
        }
        if (KEYMANAGER->isStayKeyDown(VK_DOWN))
        {
            if (offSetY2 >= WINSIZEY - backgroundSizeY)
                offSetY2 -= _controlSpeed;
            if (offSetY2 < WINSIZEY - backgroundSizeY)
            {
                offSetY2 = WINSIZEY - backgroundSizeY;
                _controlSpeed = 0;
            }
        }
    }
    else
    {

        //캐릭터용 카메라
        if (isPlayer)
        {
            //캐릭터용 카메라는 카메라의 y좌표와 캐릭터의 중점을 기준으로 속도가 달라짐

            //처음에 캐릭터까지 카메라가 자동으로 이동
            if (_state == MOVE)
            {
                _cameraSpeed = getDistance(x, y, _x, _y) * 0.035;

                dist = x - _x;
                if (dist < 0) dist = dist * -1;
                if (dist < 50) _state = FOLLOW;

                if (offSetX2 <= 0 && offSetX2 >= WINSIZEX - backgroundSizeX)
                {
                    if (x < _cameraRC.left)
                    {
                        offSetX2 += _cameraSpeed;
                        if (offSetX2 > 0) offSetX2 = 0;
                    }
                    else if (x > _cameraRC.right)
                    {
                        offSetX2 += -_cameraSpeed;
                        if (offSetX2 < WINSIZEX - backgroundSizeX)
                            offSetX2 = WINSIZEX - backgroundSizeX;
                    }
                }
                if (offSetY2 <= 0 && offSetY2 >= WINSIZEY - backgroundSizeY)
                {
                    if (y < _cameraRC.top)
                    {
                        offSetY2 += _cameraSpeed;
                        if (offSetY2 > 0) offSetY2 = 0;
                    }
                    else if (y > _cameraRC.bottom)
                    {
                        offSetY2 += -_cameraSpeed;
                        if (offSetY2 < WINSIZEY - backgroundSizeY)
                            offSetY2 = WINSIZEY - backgroundSizeY;
                    }
                }
            }
            //캐릭터에 도착했을 때 카메라(정직)
            else if (_state == FOLLOW)
            {
                _cameraSpeed = getDistance(x, y, x, _y) * 0.035;
                if (x >= WINSIZEX / 2 && x <= backgroundSizeX - WINSIZEX / 2)
                {
                    offSetX2 = -(x - (WINSIZEX / 2));
                }
                if (y >= WINSIZEY / 2 && y <= backgroundSizeY - WINSIZEY / 2)
                {
                    offSetY2 = -(y - (WINSIZEY / 2));
                }
            }
        }
        else //스무스 카메라
        {
            _state = MOVE;
            _cameraSpeed = getDistance(x, y, _x, y) * 0.035;

            //처음에 캐릭터까지 카메라가 자동으로 이동
            if (_state == MOVE)
            {
                if (offSetX2 <= 0 && offSetX2 >= WINSIZEX - backgroundSizeX)
                {
                    if (x < _cameraRC.left)
                    {
                        offSetX2 += _cameraSpeed;
                        if (offSetX2 > 0) offSetX2 = 0;
                    }
                    else if (x > _cameraRC.right)
                    {
                        offSetX2 += -_cameraSpeed;
                        if (offSetX2 < WINSIZEX - backgroundSizeX) offSetX2 = WINSIZEX - backgroundSizeX;
                    }
                }
                if (y >= WINSIZEY / 2 && y <= backgroundSizeY - WINSIZEY / 2)
                {
                    offSetY2 = -(y - (WINSIZEY / 2));
                }
                /*if (offSetY2 <= 0 && offSetY2 >= WINSIZEY - backgroundSizeY)
                {
                    if (y < _cameraRC.top)
                    {
                        offSetY2 += _cameraSpeed;
                        if (offSetY2 > 0) offSetY2 = 0;
                    }
                    else if (y > _cameraRC.bottom)
                    {
                        offSetY2 += -_cameraSpeed;
                        if (offSetY2 < WINSIZEY - backgroundSizeY) offSetY2 = WINSIZEY - backgroundSizeY;
                    }
                }*/
            }
        }
    }

    _x = WINSIZEX / 2 - offSetX2;
    _y = WINSIZEY / 2 - offSetY2;

    _cameraRC = RectMakeCenter(_x, _y, 100, 100);
    _cameraTotalRC = RectMakeCenter(_x, _y, WINSIZEX, WINSIZEY);
}

void CameraManager::render(HDC hdc)
{
    //Rectangle(IMAGEMANAGER->findImage(imageName)->getMemDC(), _cameraRC.left, _cameraRC.top, _cameraRC.right, _cameraRC.bottom);
    //Rectangle(IMAGEMANAGER->findImage(imageName)->getMemDC(), _cameraTotalRC.left, _cameraTotalRC.top, _cameraTotalRC.right, _cameraTotalRC.bottom);

    IMAGEMANAGER->findImage(imageName)->render(hdc, offSetX2, offSetY2);

    //IMGMANAGER->FindImage(imageName)->Render(hdc, 0, 0, -offSetX2, -offSetY2, WINSIZEX, WINSIZEY);
}

void CameraManager::SetState(const char * state)
{
    if (state == "MOVE")
        _state = MOVE;
    else if (state == "FOLLOW")
        _state = FOLLOW;
    else if (state == "CONTROL")
        _state = CONTROL;
}

void CameraManager::SetPos(float x, float y)
{
    _x = x;
    _y = y;
}

void CameraManager::SetSize(int sizeX, int sizeY)
{
    backgroundSizeX = sizeX;
    backgroundSizeY = sizeY;
}
