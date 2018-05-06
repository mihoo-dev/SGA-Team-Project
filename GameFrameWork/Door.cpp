#include "stdafx.h"
#include "Door.h"
#include "Player.h"

Door::Door()
{
}


Door::~Door()
{
}

HRESULT Door::init(float x, float y)
{
    Object::init(x, y);
    IMAGEMANAGER->addFrameImage("Door", "Door.bmp", 400, 120, 5, 1, true, RGB(255, 0, 255), true);

    _img = IMAGEMANAGER->findImage("Door");
    _imgName = "Door";

    _frameX = 0;
    _state = CLOSE;

    return S_OK;
}

void Door::release()
{
    Object::release();
}

void Door::update()
{
    Object::update();

    switch (_state)
    {
    case Door::CLOSE:
        if (_isCollided)
            _state = Door::OPEN;
        break;
    case Door::OPEN:
        Object::Animate();
        break;
    }
}

void Door::render()
{
    if (_inUse)
        _img->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0, 255);
}

void Door::Collision(Player * player)
{
    if (!_isCollided)
    {
        RECT temp;
        if (IntersectRect(&temp, &_rc, &player->GetColRC()))
        {
            _isCollided = true;
        }
    }
}
