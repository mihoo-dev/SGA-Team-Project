#include "stdafx.h"
#include "Object.h"


Object::Object()
{

}


Object::~Object()
{
}

HRESULT Object::init(float x, float y)
{
    _x = x;
    _y = y;
    _inUse = true;
    _isCollided = false;
    _frameX = 0;
    _frameCount = 0;

    return S_OK;
}

void Object::release()
{
}

void Object::update()
{
    if (_inUse)
        _rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void Object::render()
{
    if (_inUse)
        _img->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0, 180);
}

bool Object::Animate()
{
    _frameCount += TIMEMANAGER->getElapsedTime();
    if (_frameCount >= 0.05f)
    {
        _frameCount = 0;
        _frameX++;
        if (_frameX >= 5)
            return true;
    }
    return false;
}

void Object::Collision(RECT rc)
{
    RECT temp;
    if (IntersectRect(&temp, &_rc, &rc))
    {
        _isCollided = true;
    }
}
