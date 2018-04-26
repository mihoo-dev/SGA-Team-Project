#include "stdafx.h"
#include "Player.h"


Player::Player()
    : _x(WINSIZEX/2), _y(WINSIZEY/2),
    _direction(RIGHT), _rc({ 0, 0, 0, 0 })
{
}


Player::~Player()
{
}

HRESULT Player::init()
{
    return S_OK;
}

void Player::release()
{
}

void Player::update()
{
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
        _x += 3;
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
        _x -= 3;
    if (KEYMANAGER->isStayKeyDown(VK_UP))
        _y -= 3;
    if (KEYMANAGER->isStayKeyDown(VK_DOWN))
        _y += 3;

    if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
    {
        _direction = RIGHT;
    }
    else if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
    {
        _direction = LEFT;
    }

    _rc = RectMakeCenter(_x, _y, 20, 20);

    switch (_direction)
    {
    case Player::LEFT:
        CAMERA->update(_x - 100, _y, 3, false);
        break;
    case Player::RIGHT:
        CAMERA->update(_x + 100, _y, 3, false);
        break;
    }
    
}

void Player::render()
{
    Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}
