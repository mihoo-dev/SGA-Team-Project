#include "stdafx.h"
#include "Player.h"


Player::Player()
    : _x(WINSIZEX / 2), _y(WINSIZEY / 2),
    _direction(RIGHT), _rc({ 0, 0, 0, 0 })
{
}


Player::~Player()
{
}

HRESULT Player::init()
{
    IMAGEMANAGER->addFrameImage("Player", "Player.bmp", 1200, 200, 12, 2, true, RGB(255, 0, 255));
    _img = IMAGEMANAGER->findImage("Player");

	

    int rightIdle[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightIdle", "Player", rightIdle, 12, 10, true);

    int leftIdle[] = { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftIdle", "Player", leftIdle, 12, 10, true);

    _anim = KEYANIMANAGER->findAnimation("PlayerRightIdle");
    _anim->start();

    _state = RIGHT_IDLE;

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
        _state = RIGHT_IDLE;
        _anim = KEYANIMANAGER->findAnimation("PlayerRightIdle");
        _anim->start();
    }
    else if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
    {
        _direction = LEFT;
        _state = LEFT_IDLE;
        _anim = KEYANIMANAGER->findAnimation("PlayerLeftIdle");
        _anim->start();
    }

    switch (_state)
    {
    case Player::RIGHT_IDLE:
        break;
    case Player::LEFT_IDLE:
        break;
    }

    switch (_direction)
    {
    case Player::LEFT:
        CAMERA->update(_x - 100, _y, 3, false);
        break;
    case Player::RIGHT:
        CAMERA->update(_x + 100, _y, 3, false);
        break;
    }
    
    _rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
    KEYANIMANAGER->update();
}

void Player::render()
{
    //Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
    _img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
}
