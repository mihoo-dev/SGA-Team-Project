#include "stdafx.h"
#include "Enemy_Bunny.h"


Enemy_Bunny::Enemy_Bunny()
	:_img(nullptr),
	_state(DEFAULT),
	_x(100), _y(407),
	_countTime(0),
	_frameSpeed(5),
	_moveSpeed(3),
	_isJump(FALSE),
	_jumpPower(0),_gravity(0),
	_time(0),
	_rndTime(RND->getFromIntTo(50, 100))
{
}


Enemy_Bunny::~Enemy_Bunny()
{
}

HRESULT Enemy_Bunny::init()
{
	IMAGEMANAGER->addFrameImage("bunny_idle", "Knife Bunny_Idle.bmp", 376, 128, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bunny_jump", "Knife Bunny_Jump.bmp", 460, 144, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bunny_attack", "Knife Bunny_Attack.bmp", 336, 124, 3, 2, true, RGB(255, 0, 255));

	SetState(RIGHT_IDLE, 7);

	return S_OK;
}

void Enemy_Bunny::release()
{
}

void Enemy_Bunny::update()
{
	move();
}

void Enemy_Bunny::render()
{
	draw();
}

void Enemy_Bunny::move()
{
	if (_isRight)
	{
		if (_x + _img->getFrameWidth() > 1324)
		{
			SetState(LEFT_IDLE, 7);
		}
	}
	else
	{
		if (_x < 50)
		{
			SetState(RIGHT_IDLE, 7);
		}
	}

	if (!_isJump)
	{
		if (_time >= _rndTime)
		{
			if (_isRight)
			{
				SetState(RIGHT_JUMP, 3);
				_jumpPower = 8.0f;
				_gravity = 0.3f;
				_isJump = TRUE;
			}
			else
			{
				SetState(LEFT_JUMP, 3);
				_jumpPower = 8.0f;
				_gravity = 0.3f;
				_isJump = TRUE;
			}
			_time = 0;
		}
	}
	else
	{
		if (_isRight)
		{
			_x += _moveSpeed;
			_y -= _jumpPower;
			_jumpPower -= _gravity;
			if (_y >= 407)
			{
				SetState(RIGHT_IDLE, 7);;
				_y = 407;
				_isJump = FALSE;
				_rndTime = RND->getFromIntTo(50, 100);
			}
		}
		else
		{
			_x -= _moveSpeed;
			_y -= _jumpPower;
			_jumpPower -= _gravity;
			if (_y >= 407)
			{
				SetState(LEFT_IDLE, 7);;
				_y = 407;
				_isJump = FALSE;
				_rndTime = RND->getFromIntTo(50, 100);
			}
		}
	}

	_rc = RectMake(_x + 10, _y + 5, _img->getFrameWidth() - 20, _img->getFrameHeight() - 10);

	_time++;
	_countTime++;
	if (_isJump)
	{
		WaitAnimation(2);
	}
	else
		LoopAnimation();
}

void Enemy_Bunny::draw()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	_img->frameRender(getMemDC(), _x, _y);
}

void Enemy_Bunny::SetState(STATE state, UINT frameSpeed)
{
	_state = state; _frameSpeed = frameSpeed;
	switch (_state)
	{
	case Enemy_Bunny::LEFT_IDLE:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bunny_idle");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bunny::RIGHT_IDLE:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bunny_idle");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	case Enemy_Bunny::LEFT_JUMP:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bunny_jump");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bunny::RIGHT_JUMP:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bunny_jump");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	case Enemy_Bunny::LEFT_ATTACK:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bunny_attack");
		_img->setFrameY(1);
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bunny::RIGHT_ATTACK:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bunny_attack");
		_img->setFrameY(0);
		_currentFrameX = 0;
		break;
	}
}

void Enemy_Bunny::LoopAnimation(UINT value)
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

void Enemy_Bunny::OneShotAnimation()
{
	if (_countTime >= _frameSpeed)
	{
		if (_isRight)
		{
			_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() >= _img->getMaxFrameX())
			{
				_currentFrameX = _img->getMaxFrameX() - 1;
			}
			_currentFrameX++;
		}
		else
		{
			_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() <= 0)
			{
				_currentFrameX = 1;
			}
			_currentFrameX--;
		}

		_countTime = 0;
	}
}

void Enemy_Bunny::WaitAnimation(UINT value)
{
	if (_countTime >= _frameSpeed)
	{
		if (_isRight)
		{
			_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() >= value)
			{
				_currentFrameX = value - 1;
			}
			_currentFrameX++;
		}
		else
		{
			if (value == 0) value = _img->getMaxFrameX();
			_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() <= value)
			{
				_currentFrameX = value + 1;
			}
			_currentFrameX--;
		}

		_countTime = 0;
	}
}
