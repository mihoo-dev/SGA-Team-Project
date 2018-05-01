#include "stdafx.h"
#include "Enemy_Bear.h"


Enemy_Bear::Enemy_Bear()
	:_img(nullptr),
	_state(DEFAULT),
	_x(100),_y(247),
	_countTime(0),
	_frameSpeed(5),
	_moveSpeed(3),
	_isJump(FALSE),
	_jumpPower(0), _gravity(0),
	_time(0)
{
}


Enemy_Bear::~Enemy_Bear()
{
}

HRESULT Enemy_Bear::init()
{
	IMAGEMANAGER->addFrameImage("bear_idle", "Chainsaw Bear_Idle.bmp", 972, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_walk", "Chainsaw Bear_Walk.bmp", 1344, 444, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_back", "Chainsaw Bear_Back Walk.bmp", 1344, 444, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_run", "Chainsaw Bear_Run.bmp", 1302, 452, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_jump", "Chainsaw Bear_Jump.bmp", 1218, 468, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_roar", "Chainsaw Bear_Roar.bmp", 1692, 444, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_attack", "Chainsaw Bear_Swipe.bmp", 2640, 444, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_damage", "Chainsaw Bear_Get Hit.bmp", 1274, 452, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_die", "Chainsaw Bear_Die.bmp", 2352, 500, 12, 2, true, RGB(255, 0, 255));

	SetState(RIGHT_WALK, 7);

	return S_OK;
}

void Enemy_Bear::release()
{
}

void Enemy_Bear::update()
{
	move();
}

void Enemy_Bear::render()
{
	draw();
}

void Enemy_Bear::move()
{
	
	if (_x + _img->getFrameWidth() / 2 < _playerX)
		if (_state != RIGHT_RUN)
			SetState(RIGHT_RUN, 5);
	if (_x + _img->getFrameWidth() / 2 > _playerX)
		if (_state != LEFT_RUN)
			SetState(LEFT_RUN, 5);

	if (_state != RIGHT_ATTACK && _state != LEFT_ATTACK)
		if (_rc.right - 10 > _playerRc.left + 10 &&
			_rc.left + 10 < _playerRc.right - 10 &&
			_rc.top < _playerRc.bottom &&
			_rc.bottom > _playerRc.top)
		{
			if (_x + _img->getFrameWidth() / 2 < _playerX)
				SetState(RIGHT_ATTACK, 5);
			if (_x + _img->getFrameWidth() / 2 > _playerX)
				SetState(LEFT_ATTACK, 5);
		}

	if (_state != RIGHT_ATTACK && _state != LEFT_ATTACK)
	{
		if (_isRight) _x += _moveSpeed;
		else _x -= _moveSpeed;
	}

	_rc = RectMake(_x + 10, _y + 5, _img->getFrameWidth() - 20, _img->getFrameHeight() - 10);
	if (_state == RIGHT_ATTACK )
		_hitRc = RectMake(_rc.left + (_rc.right - _rc.left) / 2 + 50,
			_rc.top + 150, 100, 50);
	else if(_state == LEFT_ATTACK)
		_hitRc = RectMake(_rc.right - (_rc.right - _rc.left) / 2 - 150,
			_rc.top + 150, 100, 50);
	else
		_hitRc = RectMake(0, 0, 0, 0);

	_countTime++;
	if (_state == RIGHT_WALK || _state == LEFT_WALK ||
		_state == RIGHT_BACK || _state == LEFT_BACK ||
		_state == RIGHT_RUN || _state == LEFT_RUN)
		LoopAnimation();
	else
	{
		if (_isRight)
			OneShotAnimation(RIGHT_IDLE);
		else
			OneShotAnimation(LEFT_IDLE);
	}
}

void Enemy_Bear::draw()
{
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	Rectangle(getMemDC(), _hitRc.left, _hitRc.top, _hitRc.right, _hitRc.bottom);
	_img->frameRender(getMemDC(), _x, _y);
}

void Enemy_Bear::SetState(STATE state, UINT frameSpeed)
{
	_state = state; _frameSpeed = frameSpeed; _countTime = 0;
	switch (_state)
	{
	case Enemy_Bear::LEFT_IDLE:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bear_idle");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX(); 
		break;
	case Enemy_Bear::RIGHT_IDLE:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bear_idle");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	case Enemy_Bear::LEFT_WALK:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bear_walk");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bear::RIGHT_WALK:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bear_walk");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	case Enemy_Bear::LEFT_BACK:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bear_back");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bear::RIGHT_BACK:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bear_back");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	case Enemy_Bear::LEFT_RUN:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bear_run");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bear::RIGHT_RUN:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bear_run");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	case Enemy_Bear::LEFT_JUMP:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bear_jump");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bear::RIGHT_JUMP:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bear_jump");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	case Enemy_Bear::LEFT_ROAR:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bear_roar");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bear::RIGHT_ROAR:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bear_roar");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	case Enemy_Bear::LEFT_ATTACK:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bear_attack");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bear::RIGHT_ATTACK:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bear_attack");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	case Enemy_Bear::LEFT_DAMAGE:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bear_damage");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bear::RIGHT_DAMAGE:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bear_damage");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	case Enemy_Bear::LEFT_DIE:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bear_die");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bear::RIGHT_DIE:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bear_die");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	}
}

void Enemy_Bear::LoopAnimation(UINT value)
{
	if (_countTime >= _frameSpeed)
	{
		if (_isRight)
		{
			_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() >= _img->getMaxFrameX())
			{
				_currentFrameX = value - 1;
			}
			_currentFrameX++;
		}
		else
		{
			_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() <= 0)
			{
				_currentFrameX = _img->getMaxFrameX() + 1;
			}
			_currentFrameX--;
		}

		_countTime = 0;
	}
}

void Enemy_Bear::OneShotAnimation(STATE state)
{
	if (_countTime >= _frameSpeed)
	{
		if (_isRight)
		{
			_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() >= _img->getMaxFrameX())
			{
				SetState(state);
			}
			_currentFrameX++;
		}
		else
		{
			_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() <= 0)
			{
				SetState(state);
			}
			_currentFrameX--;
		}

		_countTime = 0;
	}
}
