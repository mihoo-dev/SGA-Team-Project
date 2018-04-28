#include "stdafx.h"
#include "Player.h"


Player::Player()
    : _x(WINSIZEX / 2), _y(WINSIZEY / 2),
    _speed(0.0f), _friction(0.0f),
    _jumpPower(0), _gravity(0.3f),
    _direction(RIGHT), _rc({ 0, 0, 0, 0 }),
    _onLadder(false), _onGround(false)
{
}


Player::~Player()
{
}

HRESULT Player::init()
{
    IMAGEMANAGER->addFrameImage("Player", "Player.bmp", 1600, 800, 16, 8, true, RGB(255, 0, 255));
    _img = IMAGEMANAGER->findImage("Player");

    int rightIdle[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightIdle", "Player", rightIdle, 12, 10, true);

    int leftIdle[] = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftIdle", "Player", leftIdle, 12, 10, true);

    int rightWalk[] = { 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightWalk", "Player", rightWalk, 16, 15, true);

    int leftWalk[] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftWalk", "Player", leftWalk, 16, 15, true);

    int rightRun[] = { 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightRun", "Player", rightRun, 12, 15, true);

    int leftRun[] = { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftRun", "Player", leftRun, 12, 15, true);

    int rightJump[] = { 96, 97, 98, 99 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightJump", "Player", rightJump, 4, 15, true);

    int leftJump[] = { 112, 113, 114, 115 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftJump", "Player", leftJump, 4, 15, true);

    int rightMid[] = { 100, 101, 102 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightMid", "Player", rightMid, 3, 15, false);

    int leftMid[] = { 116, 117, 118 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftMid", "Player", leftMid, 3, 15, false);

    int rightFall[] = { 103, 104, 105, 106, 107, 108 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightFall", "Player", rightFall, 6, 15, true);

    int leftFall[] = { 119, 120, 121, 122, 123, 124 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftFall", "Player", leftFall, 6, 15, true);

    int rightLand[] = { 76, 77, 78, 79, 109 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightLand", "Player", rightLand, 5, 15, false);
    
    int leftLand[] = { 92, 93, 94, 95, 125 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftLand", "Player", leftLand, 5, 15, false);

    _state = RIGHT_IDLE;
    _anim = KEYANIMANAGER->findAnimation("PlayerRightIdle");
    _anim->start();

    return S_OK;
}

void Player::release()
{
}

void Player::update()
{
    GroundCollision();

    if (_state != RIGHT_JUMP && _state != LEFT_JUMP &&
        _state != RIGHT_MID && _state != LEFT_MID &&
        _state != RIGHT_FALL && _state != LEFT_FALL &&
        _state != RIGHT_LAND && _state != LEFT_LAND)
    {
        if (!KEYMANAGER->isStayKeyDown(VK_LSHIFT))
        {
            if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
            {
                _friction = 0.5f;
                _direction = RIGHT;
                ChangeAnim(RIGHT_WALK, "PlayerRightWalk");
            }
            else if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
            {
                _friction = 0.5f;
                _direction = LEFT;
                ChangeAnim(LEFT_WALK, "PlayerLeftWalk");
            }
        }
        else
        {
            if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
            {
                _friction = 0.5f;
                _direction = RIGHT;
                ChangeAnim(RIGHT_RUN, "PlayerRightRun");
            }
            else if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
            {
                _friction = 0.5f;
                _direction = LEFT;
                ChangeAnim(LEFT_RUN, "PlayerLeftRun");
            }
        }
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        _jumpPower = 7;
        _gravity = 0.3f;

        if (_state == RIGHT_IDLE || _state == RIGHT_WALK || 
            _state == RIGHT_RUN || _state == RIGHT_JUMP ||
            _state == RIGHT_MID || _state == RIGHT_FALL)
        {
            ChangeAnim(RIGHT_JUMP, "PlayerRightJump");
        }
        else if (_state == LEFT_IDLE || _state == LEFT_WALK ||
                 _state == LEFT_RUN || _state == LEFT_JUMP ||
                 _state == LEFT_MID || _state == LEFT_FALL)
        {
            ChangeAnim(LEFT_JUMP, "PlayerLeftJump");
        }
    }

    if (KEYMANAGER->isStayKeyDown(VK_DOWN))
        if (_onLadder)
            _y += 2;
    if (KEYMANAGER->isStayKeyDown(VK_UP))
        if (_onLadder)
            _y -= 2;

    switch (_state)
    {
    case Player::RIGHT_IDLE:
        Friction("left", 0);
        break;
    case Player::LEFT_IDLE:
        Friction("right", 0);
        break;
    case Player::RIGHT_WALK:
        Friction("right", 3);

        if (!KEYMANAGER->isStayKeyDown(VK_RIGHT))
        {
            _friction = 0.5f;
            ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
        }
        if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
        {
            _friction = 0.5f;
            ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
        }
        if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
        {
            _friction = 0.5f;
            ChangeAnim(RIGHT_RUN, "PlayerRightRun");
        }
        break;
    case Player::LEFT_WALK:
        Friction("left", -3);

        if (!KEYMANAGER->isStayKeyDown(VK_LEFT))
        {
            _friction = 0.5f;
            ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
        }
        if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
        {
            _friction = 0.5f;
            ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
        }
        if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
        {
            _friction = 0.5f;
            ChangeAnim(LEFT_RUN, "PlayerLeftRun");
        }
        break;
    case Player::RIGHT_RUN:
        Friction("right", 5);

        if (!KEYMANAGER->isStayKeyDown(VK_RIGHT))
        {
            _friction = 0.5f;
            ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
        }
        if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
        {
            _friction = 0.5f;
            ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
        }
        if (KEYMANAGER->isOnceKeyUp(VK_LSHIFT))
        {
            _friction = 0.5f;
            ChangeAnim(RIGHT_WALK, "PlayerRightWalk");
        }
        break;
    case Player::LEFT_RUN:
        Friction("left", -5);

        if (!KEYMANAGER->isStayKeyDown(VK_LEFT))
        {
            _friction = 0.5f;
            ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
        }
        if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
        {
            _friction = 0.5f;
            ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
        }
        if (KEYMANAGER->isOnceKeyUp(VK_LSHIFT))
        {
            _friction = 0.5f;
            ChangeAnim(LEFT_WALK, "PlayerLeftWalk");
        }
        break;
    case Player::RIGHT_JUMP:
        if (_jumpPower <= 0) 
            ChangeAnim(RIGHT_MID, "PlayerRightMid");
        break;
    case Player::LEFT_JUMP:
        if (_jumpPower <= 0) 
            ChangeAnim(LEFT_MID, "PlayerLeftMid");
        break;
    case Player::RIGHT_MID:
        if (!_anim->isPlay()) 
            ChangeAnim(RIGHT_FALL, "PlayerRightFall");
        break;
    case Player::LEFT_MID:
        if (!_anim->isPlay())
            ChangeAnim(LEFT_FALL, "PlayerLeftFall");
        break;
    case Player::RIGHT_FALL:
        if (_onGround)
        {
            _friction = 0.5f;
            ChangeAnim(RIGHT_LAND, "PlayerRightLand");
        }
        break;
    case Player::LEFT_FALL:
        if (_onGround)
        {
            _friction = 0.5f;
            ChangeAnim(LEFT_LAND, "PlayerLeftLand");
        }
        break;
    case Player::RIGHT_LAND:
        Friction("left", 0);
        if (!_anim->isPlay())
        {
            if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
            {
                if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
                {
                    _friction = 0.5f;
                    _speed = 0;
                    ChangeAnim(RIGHT_RUN, "PlayerRightRun");
                }
                else
                {
                    _friction = 0.5f;
                    _speed = 0;
                    ChangeAnim(RIGHT_WALK, "PlayerRightWalk");
                }
            }
            else
            {
                _friction = 0.5f;
                _speed = 0;
                ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
            }
        }
        break;
    case Player::LEFT_LAND:
        Friction("right", 0);
        if (!_anim->isPlay())
        {
            if (KEYMANAGER->isStayKeyDown(VK_LEFT))
            {
                if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
                {
                    _friction = 0.5f;
                    _speed = 0;
                    ChangeAnim(LEFT_RUN, "PlayerLeftRun");
                }
                else
                {
                    _friction = 0.5f;
                    _speed = 0;
                    ChangeAnim(LEFT_WALK, "PlayerLeftWalk");
                }
            }
            else
            {
                _friction = 0.5f;
                _speed = 0;
                ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
            }
        }
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

    if (_state == RIGHT_JUMP || _state == LEFT_JUMP ||
        _state == RIGHT_MID || _state == LEFT_MID ||
        _state == RIGHT_FALL || _state == LEFT_FALL)
        _x += _speed;
    _y -= _jumpPower;
    _jumpPower -= _gravity;
    
    _rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
    
    
    KEYANIMANAGER->update();
}

void Player::render()
{
    //Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
    
    _img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
}

void Player::ChangeAnim(STATE state, string animKeyName)
{
    _state = state;
    _anim = KEYANIMANAGER->findAnimation(animKeyName);
    _anim->start();
}

void Player::Friction(string direction, float maxSpeed)
{
    if (direction == "left")
    {
        _x += _speed;
        _speed -= _friction;
        if (_speed <= maxSpeed)
        {
            _speed = maxSpeed;
            _friction = 0;
        }
    }
    else if (direction == "right")
    {
        _x += _speed;
        _speed += _friction;
        if (_speed >= maxSpeed)
        {
            _speed = maxSpeed;
            _friction = 0;
        }
    }
}

void Player::GroundCollision()
{
    _probeX = _x;
    _probeY = _y;

    //아래
    COLORREF color = RGB(255, 255, 0);

    for (int i = _probeY; i <= _probeY + _img->getFrameHeight() / 2; i++)
    {
        COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage("backgroundCol")->getMemDC(), _x, i);

        if (pixelColor == RGB(0, 255, 0))
        {
            _onLadder = true;
            _y = i - _img->getFrameHeight() / 2;
            _jumpPower = 0;
        }
        else _onLadder = false;

        if (pixelColor == color)
        {
            _onGround = true;
            _y = i - _img->getFrameHeight() / 2;
            _jumpPower = 0;
            break;
        }
        else _onGround = false;
    }

    color = RGB(0, 255, 255);

    //오른쪽
    for (int i = _probeX; i < _probeX + _img->getFrameHeight() / 2; i++)
    {
        COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage("backgroundCol")->getMemDC(), i, _y);

        if (pixelColor == color)
        {
            _x = i - _img->getFrameWidth() / 2;
            _friction = 0;
            _speed = 0;
        }
    }

    //왼쪽
    for (int i = _probeX; i > _probeX - _img->getFrameHeight() / 2; i--)
    {
        COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage("backgroundCol")->getMemDC(), i, _y);

        if (pixelColor == color)
        {
            _x = i + _img->getFrameWidth() / 2;
            _friction = 0;
            _speed = 0;
        }
    }
}
