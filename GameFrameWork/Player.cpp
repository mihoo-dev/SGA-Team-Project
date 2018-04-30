#include "stdafx.h"
#include "Player.h"


Player::Player()
    : _x(WINSIZEX / 2), _y(WINSIZEY / 2),
    _colX(WINSIZEX/2), _colY(WINSIZEY/2),
    _speed(0.0f), _friction(0.0f),
    _jumpPower(0), _gravity(0.3f),
    _direction(RIGHT), _rc({ 0, 0, 0, 0 }),
    _onLadder(false), _onGround(false),
    _item(SWORD), _isCombo(false)
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

    //플레이어 공격(무기X) 모션
    IMAGEMANAGER->addFrameImage("PlayerAttack1", "PlayerAttack(WeaponX).bmp", 1500, 1000, 6, 10, true, RGB(255, 0, 255));

    int rightDuckKick[] = { 0, 1, 2, 3, 4, 5 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightDuckKick", "PlayerAttack1", rightDuckKick, 6, 15, false);

    int leftDuckKick[] = { 6, 7, 8, 9, 10, 11 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftDuckKick", "PlayerAttack1", leftDuckKick, 6, 15, false);

    int rightDuckSlide[] = { 48, 49, 50, 51, 52, 53, 28 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightDuckSlide", "PlayerAttack1", rightDuckSlide, 7, 15, false);

    int leftDuckSlide[] = { 54, 55, 56, 57, 58, 59, 29 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftDuckSlide", "PlayerAttack1", leftDuckSlide, 7, 15, false);

    int rightPunch1[] = { 12, 13, 14 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightPunch1", "PlayerAttack1", rightPunch1, 3, 15, false);

    int leftPunch1[] = { 18, 19, 20 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftPunch1", "PlayerAttack1", leftPunch1, 3, 15, false);

    int rightPunch2[] = { 15, 16, 17 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightPunch2", "PlayerAttack1", rightPunch2, 3, 15, false);

    int leftPunch2[] = { 21, 22, 23 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftPunch2", "PlayerAttack1", leftPunch2, 3, 15, false);

    int rightPunch3[] = { 24, 25, 26, 27 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightPunch3", "PlayerAttack1", rightPunch3, 4, 15, false);

    int leftPunch3[] = { 30, 31, 32, 33 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftPunch3", "PlayerAttack1", leftPunch3, 4, 15, false);

    int rightJumpPunch[] = { 36, 37, 38, 39, 40, 41 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightJumpPunch", "PlayerAttack1", rightJumpPunch, 6, 15, false);

    int leftJumpPunch[] = { 42, 43, 44, 45, 46, 47 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftJumpPunch", "PlayerAttack1", leftJumpPunch, 6, 15, false);

    //플레이어 공격(무기O) 모션
    IMAGEMANAGER->addFrameImage("PlayerAttack2", "PlayerAttack(WeaponO).bmp", 4200, 1200, 14, 8, true, RGB(255, 0, 255));

    int rightJakePunch[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightJakePunch", "PlayerAttack2", rightJakePunch, 12, 15, false);

    int leftJakePunch[] = { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftJakePunch", "PlayerAttack2", leftJakePunch, 12, 15, false);

    int rightSword1[] = { 28, 29, 30, 31, 32, 33, 34 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightSword1", "PlayerAttack2", rightSword1, 7, 17, false);

    int leftSword1[] = { 42, 43, 44, 45, 46, 47, 48 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftSword1", "PlayerAttack2", leftSword1, 7, 17, false);

    int rightSword2[] = { 35, 36, 37, 38, 39, 40, 41 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightSword2", "PlayerAttack2", rightSword2, 7, 17, false);
    
    int leftSword2[] = { 49, 50, 51, 52, 53, 54, 55 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftSword2", "PlayerAttack2", leftSword2, 7, 17, false);

    int rightJumpSword[] = { 56, 57, 58, 59, 60, 61, 62, 63, 64, 65 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightJumpSword", "PlayerAttack2", rightJumpSword, 10, 17, false);

    int leftJumpSword[] = { 70, 71, 72, 73, 74, 75, 76, 77, 78, 79 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftJumpSword", "PlayerAttack2", leftJumpSword, 10, 17, false);

    int rightDuckSword[] = { 84, 85, 86, 87, 88, 89, 90, 91, 92 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerRightDuckSword", "PlayerAttack2", rightDuckSword, 9, 17, false);

    int leftDuckSword[] = { 98, 99, 100, 101, 102, 103, 104, 105, 106 };
    KEYANIMANAGER->addArrayFrameAnimation("PlayerLeftDuckSword", "PlayerAttack2", leftDuckSword, 9, 17, false);

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
        _state != RIGHT_LADDER_OFF && _state != LEFT_LADDER_OFF &&
        _state != RIGHT_DUCK && _state != LEFT_DUCK &&
        _state != RIGHT_DUCK_KICK && _state != LEFT_DUCK_KICK &&
        _state != RIGHT_DUCK_SLIDE && _state != LEFT_DUCK_SLIDE &&
        _state != RIGHT_DUCK_SWORD && _state != LEFT_DUCK_SWORD &&
        _state != RIGHT_PUNCH_1 && _state != LEFT_PUNCH_1 &&
        _state != RIGHT_PUNCH_2 && _state != LEFT_PUNCH_2 &&
        _state != RIGHT_PUNCH_3 && _state != LEFT_PUNCH_3 &&
        _state != RIGHT_JUMP_PUNCH && _state != LEFT_JUMP_PUNCH &&
        _state != RIGHT_JAKE_PUNCH && _state != LEFT_JAKE_PUNCH &&
        _state != RIGHT_SWORD_1 && _state != LEFT_SWORD_1 &&
        _state != RIGHT_SWORD_2 && _state != LEFT_SWORD_2 &&
        _state != RIGHT_JUMP_SWORD && _state != LEFT_JUMP_SWORD)
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
            ChangeAnim(RIGHT_DUCK, "PlayerRightDuck");
        if (_state == LEFT_JUMP)
            ChangeAnim(RIGHT_JUMP, "PlayerRightJump");
        else if (_state == LEFT_MID)
            ChangeAnim(RIGHT_MID, "PlayerRightMid");
        else if (_state == LEFT_FALL)
            ChangeAnim(RIGHT_FALL, "PlayerRightFall");
    }
    else if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
    {
        _direction = LEFT;
        if (_state == RIGHT_DUCK)
            ChangeAnim(LEFT_DUCK, "PlayerLeftDuck");
        if (_state == RIGHT_JUMP)
            ChangeAnim(LEFT_JUMP, "PlayerLeftJump");
        else if (_state == RIGHT_MID)
            ChangeAnim(LEFT_MID, "PlayerLeftMid");
        else if (_state == RIGHT_FALL)
            ChangeAnim(LEFT_FALL, "PlayerLeftFall");
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        if (_state != RIGHT_LAND && _state != LEFT_LAND)
        {
            _jumpPower = 7;
            _gravity = 0.3f;
            _img = IMAGEMANAGER->findImage("Player");

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
            _speed = 0;
            if (_direction == RIGHT)
            {
                if (_item == DEFFAULT)
                {
                    _img = IMAGEMANAGER->findImage("PlayerAttack1");
                    ChangeAnim(RIGHT_PUNCH_1, "PlayerRightPunch1");
                }
                else if (_item == SWORD)
                {
                    _img = IMAGEMANAGER->findImage("PlayerAttack2");
                    _y = _rc.bottom - _img->getFrameHeight() / 2;
                    ChangeAnim(RIGHT_SWORD_1, "PlayerRightSword1");
                }
            }
            else if (_direction == LEFT)
            {
                if (_item == DEFFAULT)
                {
                    _img = IMAGEMANAGER->findImage("PlayerAttack1");
                    ChangeAnim(LEFT_PUNCH_1, "PlayerLeftPunch1");
                }
                else if (_item == SWORD)
                {
                    _img = IMAGEMANAGER->findImage("PlayerAttack2");
                    _y = _rc.bottom - _img->getFrameHeight() / 2;
                    ChangeAnim(LEFT_SWORD_1, "PlayerLeftSword1");
                }
            }
        }
        if (KEYMANAGER->isOnceKeyDown('X'))
        {
            _speed = 0;
            _img = IMAGEMANAGER->findImage("PlayerAttack2");
            _y = _rc.bottom - _img->getFrameHeight() / 2;
            if (_direction == RIGHT)
               ChangeAnim(RIGHT_JAKE_PUNCH, "PlayerRightJakePunch");
            else if (_direction == LEFT)
               ChangeAnim(LEFT_JAKE_PUNCH, "PlayerLeftJakePunch");
        }
    }

    if (_state == RIGHT_JUMP || _state == LEFT_JUMP ||
        _state == RIGHT_MID || _state == LEFT_MID ||
        _state == RIGHT_FALL || _state == LEFT_FALL)
    {
        if (KEYMANAGER->isOnceKeyDown('Z'))
        {
            if (_item == DEFFAULT)
            {
                _img = IMAGEMANAGER->findImage("PlayerAttack1");
                if (_direction == RIGHT)
                    ChangeAnim(RIGHT_JUMP_PUNCH, "PlayerRightJumpPunch");
                else if (_direction == LEFT)
                    ChangeAnim(LEFT_JUMP_PUNCH, "PlayerLeftJumpPunch");
            }
            else if (_item == SWORD)
            {
                _img = IMAGEMANAGER->findImage("PlayerAttack2");
                _y = _rc.bottom - _img->getFrameHeight() / 2;
                if (_direction == RIGHT)
                    ChangeAnim(RIGHT_JUMP_SWORD, "PlayerRightJumpSword");
                else if (_direction == LEFT)
                    ChangeAnim(LEFT_JUMP_SWORD, "PlayerLeftJumpSword");
            }
        }
    }
    

    switch (_state)
    {
    case Player::RIGHT_IDLE:
        Friction("left", 0);

        if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
        {
            if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
            {
                _friction = 0.5f;
                ChangeAnim(RIGHT_RUN, "PlayerRightRun");
            }
        }
        else
        {
            if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
            {
                _friction = 0.5f;
                ChangeAnim(RIGHT_WALK, "PlayerRightWalk");
            }
        }
        break;
    case Player::LEFT_IDLE:
        Friction("right", 0);

        if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
        {
            if (KEYMANAGER->isStayKeyDown(VK_LEFT))
            {
                _friction = 0.5f;
                ChangeAnim(LEFT_RUN, "PlayerLeftRun");
            }
        }
        else
        {
            if (KEYMANAGER->isStayKeyDown(VK_LEFT))
            {
                _friction = 0.5f;
                ChangeAnim(LEFT_WALK, "PlayerLeftWalk");
            }
        }
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
        _colY += 2;
        _y += 2;
        if (!_anim->isPlay())
        {
            ChangeAnim(LADDER_UP, "PlayerLadderUp");
        }
        break;
    case Player::LEFT_LADDER_ON:
        _colY += 2;
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
                _colY -= 2;
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
                _colY += 2;
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
        _colY -= 2.5f;
        _y -= 2.5f;
        if (!_anim->isPlay())
        {
            ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
        }
        break;
    case Player::LEFT_LADDER_OFF:
        _colY -= 2.5f;
        _y -= 2.5f;
        if (!_anim->isPlay())
        {
            ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
        }
        break;
    case Player::RIGHT_DUCK:
        if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
        {
            if (KEYMANAGER->isOnceKeyDown('Z'))
            {
                _speed = 5;
                _friction = 0.1f;
                _img = IMAGEMANAGER->findImage("PlayerAttack1");
                ChangeAnim(RIGHT_DUCK_SLIDE, "PlayerRightDuckSlide");
            }
        }
        else
        {
            if (KEYMANAGER->isOnceKeyDown('Z'))
            {
                if (_item == DEFFAULT)
                {
                    _img = IMAGEMANAGER->findImage("PlayerAttack1");
                    ChangeAnim(RIGHT_DUCK_KICK, "PlayerRightDuckKick");
                }
                else if (_item == SWORD)
                {
                    _img = IMAGEMANAGER->findImage("PlayerAttack2");
                    _y = _rc.bottom - _img->getFrameHeight() / 2;
                    ChangeAnim(RIGHT_DUCK_SWORD, "PlayerRightDuckSword");
                }
            }
        }
        if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
            ChangeAnim(RIGHT_WALK, "PlayerRightWalk");
        break;
    case Player::LEFT_DUCK:
        if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
        {
            if (KEYMANAGER->isOnceKeyDown('Z'))
            {
                _speed = -5;
                _friction = 0.1f;
                _img = IMAGEMANAGER->findImage("PlayerAttack1");
                ChangeAnim(LEFT_DUCK_SLIDE, "PlayerLeftDuckSlide");
            }
        }
        else
        {
            if (KEYMANAGER->isOnceKeyDown('Z'))
            {
                if (_item == DEFFAULT)
                {
                    _img = IMAGEMANAGER->findImage("PlayerAttack1");
                    ChangeAnim(LEFT_DUCK_KICK, "PlayerLeftDuckKick");
                }
                else if (_item == SWORD)
                {
                    _img = IMAGEMANAGER->findImage("PlayerAttack2");
                    _y = _rc.bottom - _img->getFrameHeight() / 2;
                    ChangeAnim(RIGHT_DUCK_SWORD, "PlayerRightDuckSword");
                }
            }
        }
        if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
            ChangeAnim(LEFT_WALK, "PlayerLeftWalk");
        break;
    case Player::RIGHT_DUCK_KICK:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(RIGHT_DUCK, "PlayerRightDuck");
        }
        break;
    case Player::LEFT_DUCK_KICK:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(LEFT_DUCK, "PlayerLeftDuck");
        }
        break;
    case Player::RIGHT_DUCK_SLIDE:
        Friction("left", 0);
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(RIGHT_DUCK, "PlayerRightDuck");
        }
        break;
    case Player::LEFT_DUCK_SLIDE:
        Friction("right", 0);
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(LEFT_DUCK, "PlayerLeftDuck");
        }
        break;
    case Player::RIGHT_PUNCH_1:
        if (KEYMANAGER->isOnceKeyDown('Z'))
            _isCombo = true;
        if (_isCombo)
        {
            if (!_anim->isPlay())
            {
                _isCombo = false;
                ChangeAnim(RIGHT_PUNCH_2, "PlayerRightPunch2");
            }
        }
        else
        {
            if (!_anim->isPlay())
            {
                _img = IMAGEMANAGER->findImage("Player");
                ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
            }
        }
        break;
    case Player::LEFT_PUNCH_1:
        if (KEYMANAGER->isOnceKeyDown('Z'))
            _isCombo = true;
        if (_isCombo)
        {
            if (!_anim->isPlay())
            {
                _isCombo = false;
                ChangeAnim(LEFT_PUNCH_2, "PlayerLeftPunch2");
            }
        }
        else
        {
            if (!_anim->isPlay())
            {
                _img = IMAGEMANAGER->findImage("Player");
                ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
            }
        }
        break;
    case Player::RIGHT_PUNCH_2:
        if (KEYMANAGER->isOnceKeyDown('Z'))
            _isCombo = true;
        if (_isCombo)
        {
            if (!_anim->isPlay())
            {
                _isCombo = false;
                ChangeAnim(RIGHT_PUNCH_3, "PlayerRightPunch3");
            }
        }
        else
        {
            if (!_anim->isPlay())
            {
                _img = IMAGEMANAGER->findImage("Player");
                ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
            }
        }
        break;
    case Player::LEFT_PUNCH_2:
        if (KEYMANAGER->isOnceKeyDown('Z'))
            _isCombo = true;
        if (_isCombo)
        {
            if (!_anim->isPlay())
            {
                _isCombo = false;
                ChangeAnim(LEFT_PUNCH_3, "PlayerLeftPunch3");
            }
        }
        else
        {
            if (!_anim->isPlay())
            {
                _img = IMAGEMANAGER->findImage("Player");
                ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
            }
        }
        break;
    case Player::RIGHT_PUNCH_3:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
        }
        break;
    case Player::LEFT_PUNCH_3:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
        }
        break;
    case Player::RIGHT_JUMP_PUNCH:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(RIGHT_FALL, "PlayerRightFall");
        }
        break;
    case Player::LEFT_JUMP_PUNCH:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(LEFT_FALL, "PlayerLeftFall");
        }
        break;
    case Player::RIGHT_JAKE_PUNCH:
        if (!_anim->isPlay())
        {
            _y = _rc.bottom - 50;
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
        }
        break;
    case Player::LEFT_JAKE_PUNCH:
        if (!_anim->isPlay())
        {
            _y = _rc.bottom - 50;
            _img = IMAGEMANAGER->findImage("Player");
            ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
        }
        break;
    case Player::RIGHT_SWORD_1:
        if (KEYMANAGER->isOnceKeyDown('Z'))
            _isCombo = true;
        if (_isCombo)
        {
            if (!_anim->isPlay())
            {
                _isCombo = false;
                ChangeAnim(RIGHT_SWORD_2, "PlayerRightSword2");
            }
        }
        else
        {
            if (!_anim->isPlay())
            {
                _img = IMAGEMANAGER->findImage("Player");
                _y = _rc.bottom - _img->getFrameHeight() / 2;
                ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
            }
        }
        break;
    case Player::LEFT_SWORD_1:
        if (KEYMANAGER->isOnceKeyDown('Z'))
            _isCombo = true;
        if (_isCombo)
        {
            if (!_anim->isPlay())
            {
                _isCombo = false;
                ChangeAnim(LEFT_SWORD_2, "PlayerLeftSword2");
            }
        }
        else
        {
            if (!_anim->isPlay())
            {
                _img = IMAGEMANAGER->findImage("Player");
                _y = _rc.bottom - _img->getFrameHeight() / 2;
                ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
            }
        }
        break;
    case Player::RIGHT_SWORD_2:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            _y = _rc.bottom - _img->getFrameHeight() / 2;
            ChangeAnim(RIGHT_IDLE, "PlayerRightIdle");
        }
        break;
    case Player::LEFT_SWORD_2:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            _y = _rc.bottom - _img->getFrameHeight() / 2;
            ChangeAnim(LEFT_IDLE, "PlayerLeftIdle");
        }
        break;
    case Player::RIGHT_JUMP_SWORD:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            _y = _rc.bottom - _img->getFrameHeight() / 2;
            ChangeAnim(RIGHT_FALL, "PlayerRightFall");
        }
        break;
    case Player::LEFT_JUMP_SWORD:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            _y = _rc.bottom - _img->getFrameHeight() / 2;
            ChangeAnim(LEFT_FALL, "PlayerLeftFall");
        }
        break;
    case Player::RIGHT_DUCK_SWORD:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            _y = _rc.bottom - _img->getFrameHeight() / 2;
            ChangeAnim(RIGHT_DUCK, "PlayerRightDuck");
        }
        break;
    case Player::LEFT_DUCK_SWORD:
        if (!_anim->isPlay())
        {
            _img = IMAGEMANAGER->findImage("Player");
            _y = _rc.bottom - _img->getFrameHeight() / 2;
            ChangeAnim(LEFT_DUCK, "PlayerLeftDuck");
        }
        break;
    }

    switch (_direction)
    {
    case Player::LEFT:
        CAMERA->update(_colX - 100, _colY, 3, false);
        break;
    case Player::RIGHT:
        CAMERA->update(_colX + 100, _colY, 3, false);
        break;
    }

    if (_state == RIGHT_JUMP || _state == LEFT_JUMP ||
        _state == RIGHT_MID || _state == LEFT_MID ||
        _state == RIGHT_FALL || _state == LEFT_FALL ||
        _state == RIGHT_JUMP_PUNCH || _state == LEFT_JUMP_PUNCH)
    {
        _colX += _speed;
        _x += _speed;
    }
    if (_state != RIGHT_LADDER_ON && _state != LEFT_LADDER_ON &&
        _state != LADDER_UP && _state != LADDER_DOWN && 
        _state != RIGHT_LADDER_OFF && _state != LEFT_LADDER_OFF)
    {
        _colY -= _jumpPower;
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
    _colRC = RectMakeCenter(_colX, _colY, 100, 100);
    
    KEYANIMANAGER->update();
}

void Player::render()
{
    //Rectangle(getMemDC(), _colRC.left, _colRC.top, _colRC.right, _colRC.bottom);
    
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
        _colX += _speed;
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
        _colX += _speed;
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
                    _colY = i - 50;
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
            if (_state == RIGHT_IDLE || _state == LEFT_IDLE ||
                _state == RIGHT_WALK || _state == LEFT_WALK ||
                _state == RIGHT_RUN || _state == LEFT_RUN)
            {
                if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
                {
                    if (_direction == RIGHT)
                        ChangeAnim(RIGHT_DUCK, "PlayerRightDuck");
                    else if (_direction == LEFT)
                        ChangeAnim(LEFT_DUCK, "PlayerLeftDuck");
                }
            }
            _onGround = true;
            _colY = i - 50;
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
            _colX = i - 50;
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
            _colX = i + 50;
            _x = i + _img->getFrameWidth() / 2;
            _friction = 0;
            _speed = 0;
        }
    }
}
