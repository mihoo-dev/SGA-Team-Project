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
    IMAGEMANAGER->addFrameImage("Player", "Player.bmp", 1600, 1100, 16, 11, true, RGB(255, 0, 255));
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
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightLand", "Player", rightLand, 5, 20, false);
    
    int leftLand[] = { 92, 93, 94, 95, 125 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftLand", "Player", leftLand, 5, 20, false);

    int rightLadderOn[] = { 128, 129, 130, 131, 132, 133, 134,135, 136 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightLadderOn", "Player", rightLadderOn, 9, 15, false);

    int leftLadderOn[] = { 144, 145, 146, 147, 148, 149, 150, 151, 152 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftLadderOn", "Player", leftLadderOn, 9, 15, false);

    int ladderUp[] = { 160, 161, 162, 163, 164, 165, 166, 167, 168, 169 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLadderUp", "Player", ladderUp, 10, 15, true);

    int ladderDown[] = { 169, 168, 167, 166, 165, 164, 163, 162, 161, 160 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLadderDown", "Player", ladderDown, 10, 15, true);

    int rightLadderOff[] = { 136, 135, 134, 133, 132, 131, 130, 129, 128 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightLadderOff", "Player", rightLadderOff, 9, 15, false);

    int leftLadderOff[] = { 152, 151, 150, 149, 148, 147, 146, 145, 144 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftLadderOff", "Player", leftLadderOff, 9, 15, false);

    int rightDuck[] = { 12, 13 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightDuck", "Player", rightDuck, 2, 2, true);

    int leftDuck[] = { 14, 15 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftDuck", "Player", leftDuck, 2, 2, true);

    //플레이어 공격 모션
    IMAGEMANAGER->addFrameImage("PlayerAttack", "PlayerAttack.bmp", 1500, 800, 6, 8, true, RGB(255, 0, 255));

    int rightDuckKick[] = { 0, 1, 2, 3, 4, 5 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightDuckKick", "PlayerAttack", rightDuckKick, 6, 15, false);

    int leftDuckKick[] = { 6, 7, 8, 9, 10, 11 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftDuckKick", "PlayerAttack", leftDuckKick, 6, 15, false);

    int rightAttack1[] = { 12, 13, 14 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightAttack1", "PlayerAttack", rightAttack1, 3, 15, false);

    int leftAttack1[] = { 18, 19, 20 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftAttack1", "PlayerAttack", leftAttack1, 3, 15, false);

    int rightAttack2[] = { 15, 16, 17 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightAttack2", "PlayerAttack", rightAttack2, 3, 15, false);

    int leftAttack2[] = { 21, 22, 23 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftAttack2", "PlayerAttack", leftAttack2, 3, 15, false);

    int rightAttack3[] = { 24, 25, 26, 27 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightAttack3", "PlayerAttack", rightAttack3, 4, 15, false);

    int leftAttack3[] = { 30, 31, 32, 33 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftAttack3", "PlayerAttack", leftAttack3, 4, 15, false);

    int rightJumpAttack[] = { 36, 37, 38, 39, 40, 41 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightJumpAttack", "PlayerAttack", rightJumpAttack, 6, 15, false);

    int leftJumpAttack[] = { 42, 43, 44, 45, 46, 47 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftJumpAttack", "PlayerAttack", leftJumpAttack, 6, 15, false);

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
        _state != RIGHT_LAND && _state != LEFT_LAND &&
        _state != RIGHT_LADDER_ON && _state != LEFT_LADDER_ON &&
        _state != RIGHT_DUCK && _state != LEFT_DUCK &&
        _state != RIGHT_DUCK_KICK && _state != LEFT_DUCK_KICK &&
        _state != RIGHT_ATTACK_1 && _state != LEFT_ATTACK_1 &&
        _state != RIGHT_ATTACK_2 && _state != LEFT_ATTACK_2 &&
        _state != RIGHT_ATTACK_3 && _state != LEFT_ATTACK_3)
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
    if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
    {
        _direction = RIGHT;
        if (_state == LEFT_DUCK)
        {
            _state = RIGHT_DUCK;
            _anim = KEYANIMANAGER->findAnimation("PlayerRightDuck");
        }
        if (_state == LEFT_JUMP)
        {
            _state = RIGHT_JUMP;
            _anim = KEYANIMANAGER->findAnimation("PlayerRightJump");
        }
        else if (_state == LEFT_MID)
        {
            _state = RIGHT_MID;
            _anim = KEYANIMANAGER->findAnimation("PlayerRightMid");
        }
        else if (_state == LEFT_FALL)
        {
            _state = RIGHT_FALL;
            _anim = KEYANIMANAGER->findAnimation("PlayerRightFall");
        }
        _anim->start();
    }
    else if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
    {
        _direction = LEFT;
        if (_state == RIGHT_DUCK)
        {
            _state = LEFT_DUCK;
            _anim = KEYANIMANAGER->findAnimation("PlayerLeftDuck");
        }
        if (_state == RIGHT_JUMP)
        {
            _state = LEFT_JUMP;
            _anim = KEYANIMANAGER->findAnimation("PlayerLeftJump");
        }
        else if (_state == RIGHT_MID)
        {
            _state = LEFT_MID;
            _anim = KEYANIMANAGER->findAnimation("PlayerLeftMid");
        }
        else if (_state == RIGHT_FALL)
        {
            _state = LEFT_FALL;
            _anim = KEYANIMANAGER->findAnimation("PlayerLeftFall");
        }
        _anim->start();
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        if (_state != RIGHT_LAND && _state != LEFT_LAND)
        {
            _jumpPower = 7;
            _gravity = 0.3f;

            if (_direction == RIGHT)
            {
                ChangeAnim(RIGHT_JUMP, "PlayerRightJump");
            }
            else if (_direction == LEFT)
            {
                ChangeAnim(LEFT_JUMP, "PlayerLeftJump");
            }
        }
    }

    if (_state == RIGHT_IDLE || _state == LEFT_IDLE ||
        _state == RIGHT_WALK || _state == LEFT_WALK ||
        _state == RIGHT_RUN || _state == LEFT_RUN)
    {
        if (KEYMANAGER->isOnceKeyDown('Z'))
        {
            _img = IMAGEMANAGER->findImage("PlayerAttack");
            if (_direction == RIGHT)
                ChangeAnim(RIGHT_ATTACK_1, "PlayerRightAttack1");
            else if (_direction == LEFT)
                ChangeAnim(LEFT_ATTACK_1, "PlayerLeftAttack1");
        }
    }

    if (_state == RIGHT_JUMP || _state == LEFT_JUMP ||
        _state == RIGHT_MID || _state == LEFT_MID ||
        _state == RIGHT_FALL || _state == LEFT_FALL)
    {
        if (KEYMANAGER->isOnceKeyDown('Z'))
        {
            _img = IMAGEMANAGER->findImage("PlayerAttack");
            if (_direction == RIGHT)
                ChangeAnim(RIGHT_JUMP_ATTACK, "PlayerRightJumpAttack");
            else if (_direction == LEFT)
                ChangeAnim(LEFT_JUMP_ATTACK, "PlayerLeftJumpAttack");
        }
    }
    

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
    case Player::RIGHT_LADDER_ON:
        _y += 2;
        if (!_anim->isPlay())
        {
            ChangeAnim(LADDER_UP, "PlayerLadderUp");
        }
        break;
    case Player::LEFT_LADDER_ON:
        _y += 2;
        if (!_anim->isPlay())
        {
            ChangeAnim(LADDER_UP, "PlayerLadderUp");
        }
        break;
    case Player::LADDER_UP:
        if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
            ChangeAnim(LADDER_DOWN, "PlayerLadderDown");
        if (KEYMANAGER->isStayKeyDown(VK_UP))
        {
            if (_onLadder && (_state != RIGHT_LADDER_ON && _state != LEFT_LADDER_ON))
            {
                _y -= 2;
                _anim->resume();
            }
        }
        else if (!KEYMANAGER->isStayKeyDown(VK_UP))
        {
            _anim->pause();
        }
        break;
    case Player::LADDER_DOWN:
        if (KEYMANAGER->isOnceKeyDown(VK_UP))
            ChangeAnim(LADDER_UP, "PlayerLadderUp");
        if (KEYMANAGER->isStayKeyDown(VK_DOWN))
        {
            if (_onLadder && (_state != RIGHT_LADDER_ON && _state != LEFT_LADDER_ON))
            {
                _y += 2;
                _anim->resume();
            }
        }
        else if (!KEYMANAGER->isStayKeyDown(VK_DOWN))
        {
            _anim->pause();
        }

        break;
    case Player::RIGHT_LADDER_OFF:
        _y -= 2.5f;
        if (!_anim->isPlay())
        {
            ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
        }
        break;
    case Player::LEFT_LADDER_OFF:
        _y -= 2.5f;
        if (!_anim->isPlay())
        {
            ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
        }
        break;
    case Player::RIGHT_DUCK:
        if (KEYMANAGER->isOnceKeyDown('Z'))
        {
            _speed = 4;
            _friction = 0.1f;
            _img = IMAGEMANAGER->findImage("PlayerAttack");
            ChangeAnim(RIGHT_DUCK_KICK, "PlayerRightDuckKick");
        }
        if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
            ChangeAnim(RIGHT_WALK, "PlayerRightWalk");
        break;
    case Player::LEFT_DUCK:
        if (KEYMANAGER->isOnceKeyDown('Z'))
        {
            _speed = -4;
            _friction = 0.1f;
            _img = IMAGEMANAGER->findImage("PlayerAttack");
            ChangeAnim(LEFT_DUCK_KICK, "PlayerLeftDuckKick");
        }
        if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
            ChangeAnim(LEFT_WALK, "PlayerLeftWalk");
        break;
    case Player::RIGHT_DUCK_KICK:
        Friction("left", 0);
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(RIGHT_DUCK, "PlayerRightDuck");
        }
        break;
    case Player::LEFT_DUCK_KICK:
        Friction("right", 0);
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(LEFT_DUCK, "PlayerLeftDuck");
        }
        break;
    case Player::RIGHT_ATTACK_1:
        if (KEYMANAGER->isOnceKeyDown('Z'))
        {
            ChangeAnim(RIGHT_ATTACK_2, "PlayerRightAttack2");
            break;
        }
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(RIGHT_WALK, "PlayerRightWalk");
        }
        break;
    case Player::LEFT_ATTACK_1:
        if (KEYMANAGER->isOnceKeyDown('Z'))
        {
            ChangeAnim(LEFT_ATTACK_2, "PlayerLeftAttack2");
            break;
        }
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(LEFT_WALK, "PlayerLeftWalk");
        }
        break;
    case Player::RIGHT_ATTACK_2:
        if (KEYMANAGER->isOnceKeyDown('Z'))
        {
            ChangeAnim(RIGHT_ATTACK_3, "PlayerRightAttack3");
            break;
        }
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(RIGHT_WALK, "PlayerRightWalk");
        }
        break;
    case Player::LEFT_ATTACK_2:
        if (KEYMANAGER->isOnceKeyDown('Z'))
        {
            ChangeAnim(LEFT_ATTACK_3, "PlayerLeftAttack3");
            break;
        }
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(LEFT_WALK, "PlayerLeftWalk");
        }
        break;
    case Player::RIGHT_ATTACK_3:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(RIGHT_WALK, "PlayerRightWalk");
        }
        break;
    case Player::LEFT_ATTACK_3:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(LEFT_WALK, "PlayerLeftWalk");
        }
        break;
    case Player::RIGHT_JUMP_ATTACK:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(RIGHT_FALL, "PlayerRightFall");
        }
        break;
    case Player::LEFT_JUMP_ATTACK:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(LEFT_FALL, "PlayerLeftFall");
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
        _state == RIGHT_FALL || _state == LEFT_FALL ||
        _state == RIGHT_JUMP_ATTACK || _state == LEFT_JUMP_ATTACK)
        _x += _speed;
    if (_state != RIGHT_LADDER_ON && _state != LEFT_LADDER_ON &&
        _state != LADDER_UP && _state != LADDER_DOWN && 
        _state != RIGHT_LADDER_OFF && _state != LEFT_LADDER_OFF)
    {
        _y -= _jumpPower;
        _jumpPower -= _gravity;
    }

    if (_jumpPower < -1)
    {
        if (_state == RIGHT_IDLE || _state == LEFT_IDLE ||
            _state == RIGHT_RUN || _state == LEFT_RUN)
        {
            if (_direction == RIGHT)
            {
                ChangeAnim(RIGHT_MID, "PlayerRightMid");
            }
            else if (_direction == LEFT)
            {
                ChangeAnim(LEFT_MID, "PlayerLeftMid");
            }
        }
    }
    
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

        if (pixelColor == RGB(255, 0, 0))
        {
            if (_state != RIGHT_LADDER_ON && _state != LEFT_LADDER_ON &&
                _state != LADDER_UP && _state != LADDER_DOWN)
            {
                if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
                {
                    if (_direction == RIGHT)
                    {
                        ChangeAnim(RIGHT_LADDER_ON, "PlayerRightLadderOn");
                    }
                    else if (_direction == LEFT)
                    {
                        ChangeAnim(LEFT_LADDER_ON, "PlayerLeftLadderOn");
                    }
                }
                if (_state != RIGHT_LADDER_OFF && _state != LEFT_LADDER_OFF)
                {
                    _onGround = true;
                    _y = i - _img->getFrameHeight() / 2;
                    _jumpPower = 0;
                }
            }
            break;
        }
        if (pixelColor == RGB(0, 255, 0))
        {
            _onLadder = true;
            if (_onLadder && _state != RIGHT_LADDER_ON && _state != LEFT_LADDER_ON &&
                _state != LADDER_UP && _state != LADDER_DOWN)
            {
                if (KEYMANAGER->isOnceKeyDown(VK_UP))
                {
                    if (_direction == RIGHT)
                    {
                        _state = RIGHT_LADDER_ON;
                        _anim = KEYANIMANAGER->findAnimation("PlayerRightLadderOn");
                    }
                    else if (_direction == LEFT)
                    {
                        _state = LEFT_LADDER_ON;
                        _anim = KEYANIMANAGER->findAnimation("PlayerLeftLadderOn");
                    }
                }
            }
        }
        else _onLadder = false;

        if (pixelColor == color)
        {
            if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
            {
                if (_direction == RIGHT)
                    ChangeAnim(RIGHT_DUCK, "PlayerRightDuck");
                else if (_direction == LEFT)
                    ChangeAnim(LEFT_DUCK, "PlayerLeftDuck");
            }
            _onGround = true;
            _y = i - _img->getFrameHeight() / 2;
            _jumpPower = 0;
            break;
        }
        else _onGround = false;
    }

    //위
    for (int i = _probeY; i >= _probeY - _img->getFrameHeight() / 2 + 10; i--)
    {
        COLORREF pixelColor = GetPixel(IMAGEMANAGER->findImage("backgroundCol")->getMemDC(), _x, i);

        if (pixelColor == RGB(255, 0, 255))
        {
            if (_state == LADDER_UP)
            {
                if (_onLadder)
                {
                    if (KEYMANAGER->isStayKeyDown(VK_UP))
                    {
                        if (_direction == RIGHT)
                            ChangeAnim(RIGHT_LADDER_OFF, "PlayerRightLadderOff");
                        else if(_direction == LEFT)
                            ChangeAnim(LEFT_LADDER_OFF, "PlayerLeftLadderOff");
                    }
                }
            }
        }
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
