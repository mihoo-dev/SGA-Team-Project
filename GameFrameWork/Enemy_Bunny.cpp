#include "stdafx.h"
#include "Enemy_Bunny.h"


Enemy_Bunny::Enemy_Bunny()
	:_img(nullptr),
	_state(DEFAULT),
	_x(100), _y(300),
	_countTime(0),
	_frameSpeed(5),
	_moveSpeed(3),
	_isJump(FALSE),
	_jumpPower(0), _gravity(0),
	_time(0),
	_rndTime(RND->getFromIntTo(100, 200)),
	_hp(4),
	_isDamage(false),
	_isPlayerDamage(false)
{
}


Enemy_Bunny::~Enemy_Bunny()
{
}

HRESULT Enemy_Bunny::init(float x, float y)
{
	SetState(RIGHT_IDLE, 7);

	_x = x;
	_y = y;

	return S_OK;
}

void Enemy_Bunny::release()
{
}

void Enemy_Bunny::update()
{
	Move();
}

void Enemy_Bunny::render()
{
	Draw();
}

void Enemy_Bunny::Move()
{
	if (_state != LEFT_JUMP && _state != RIGHT_JUMP)
	{
		if (_x - 200 > _playerX) SetState(LEFT_IDLE);
		else if (_x + _img->getFrameWidth() + 200 < _playerX) SetState(RIGHT_IDLE);
	}

	Jump();

	_time++;
	_countTime++;

	//렉트 설정
	_rc = RectMake(_x + 10, _y + 5, _img->getFrameWidth() - 20, _img->getFrameHeight() - 10);
	if (_isRight)
		_hitRc = RectMakeCenter(_rc.right, _rc.bottom - 30, 10, 10);
	else
		_hitRc = RectMakeCenter(_rc.left, _rc.bottom - 30, 10, 10);

	if (_isJump)
	{
		//2프레임에서 멈춘다
		StopAnimation(2);
	}
	else
		LoopAnimation();
}

void Enemy_Bunny::Draw()
{
	if (_x + _img->getFrameWidth() >= CAMERA->GetX() &&
		_x <= CAMERA->GetRC().right)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		Rectangle(getMemDC(), _hitRc.left, _hitRc.top, _hitRc.right, _hitRc.bottom);
		_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
	}
}

void Enemy_Bunny::Jump()
{
	//점프하는게 아니면
	if (!_isJump)
	{
		//랜덤시간만큼 기다린다
		if (_time >= _rndTime)
		{
			//오른쪽 방향이면
			if (_isRight)
			{
				//오른쪽으로 점프한다
				SetState(RIGHT_JUMP, 4);
				_jumpPower = 8.0f;
				_gravity = 0.3f;
				_isJump = true;
			}
			//왼쪽 방향이면
			else
			{
				//왼쪽으로 점프한다
				SetState(LEFT_JUMP, 4);
				_jumpPower = 8.0f;
				_gravity = 0.3f;
				_isJump = true;
			}
			_time = 0;
		}
		else
		{
			_y += 5.0f;
		}
		PixelCollision2();
	}
	//점프하고 있으면
	else
	{
		//오른쪽
		if (_isRight)
		{
			//오른쪽으로 이동속도만큼 이동한다
			_x += _moveSpeed;
			_y -= _jumpPower;
			_jumpPower -= _gravity;
		}
		else
		{
			_x -= _moveSpeed;
			_y -= _jumpPower;
			_jumpPower -= _gravity;
		}
		PixelCollision1();
	}
}

//상태에 따른 시작 프레임 번호 설정 & 이미지 설정 & 방향 설정
void Enemy_Bunny::SetState(STATE state, UINT frameSpeed)
{
	_state = state; _frameSpeed = frameSpeed;
	switch (_state)
	{
	case Enemy_Bunny::LEFT_IDLE:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bunny_idle");
		//_img->setFrameY(1);
		_currentFrameY = 1;
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bunny::RIGHT_IDLE:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bunny_idle");
		//_img->setFrameY(0);
		_currentFrameY = 0;
		_currentFrameX = 0;
		break;
	case Enemy_Bunny::LEFT_JUMP:
		_isRight = FALSE;
		_img = IMAGEMANAGER->findImage("bunny_jump");
		//_img->setFrameY(1);
		_currentFrameY = 1;
		_currentFrameX = _img->getMaxFrameX();
		break;
	case Enemy_Bunny::RIGHT_JUMP:
		_isRight = TRUE;
		_img = IMAGEMANAGER->findImage("bunny_jump");
		//_img->setFrameY(0);
		_currentFrameY = 0;
		_currentFrameX = 0;
		break;
	}
}

void Enemy_Bunny::PixelCollision1()
{
	_probeX = _x + _img->getFrameWidth() / 2;
	_probeY = _y + _img->getFrameHeight() / 2;

	if (_isRight)
		//RIGHT
		for (int i = _probeX; i <= _probeX + _img->getFrameWidth() / 2; ++i)
		{
			COLORREF pixel = GetPixel(IMAGEMANAGER->findImage("Ground_Pixel")->getMemDC(),
				i, _probeY);

			if (pixel == RGB(0, 255, 255))
			{
				_x = i - _img->getFrameWidth();
			}
		}
	else
		//LEFT
		for (int i = _probeX; i >= _probeX - _img->getFrameWidth() / 2; --i)
		{
			COLORREF pixel = GetPixel(IMAGEMANAGER->findImage("Ground_Pixel")->getMemDC(),
				i, _probeY);

			if (pixel == RGB(0, 255, 255))
			{
				_x = i;
			}
		}

	//BOTTOM
	for (int i = _probeY; i <= _probeY + _img->getFrameHeight() / 2; ++i)
	{
		COLORREF pixel = GetPixel(IMAGEMANAGER->findImage("Ground_Pixel")->getMemDC(),
			_probeX, i);

		if (pixel == RGB(255, 255, 0))
		{
			_y = i - _img->getFrameHeight() + 7;
			_rndTime = RND->getFromIntTo(100, 200);
			_isJump = false;
			if (_isRight) SetState(RIGHT_IDLE);
			else SetState(LEFT_IDLE);
			break;
		}
	}
}

void Enemy_Bunny::PixelCollision2()
{
	_probeX = _x + _img->getFrameWidth() / 2;
	_probeY = _y + _img->getFrameHeight() / 2;

	for (int i = _probeY; i <= _probeY + _img->getFrameHeight() / 2; ++i)
	{
		COLORREF pixel = GetPixel(IMAGEMANAGER->findImage("Ground_Pixel")->getMemDC(),
			_probeX, i);

		if (pixel == RGB(255, 255, 0))
		{
			_y = i - _img->getFrameHeight();
			break;
		}
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
			//_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() >= _img->getMaxFrameX())
			{
				_currentFrameX = _img->getMaxFrameX() - 1;
			}
			_currentFrameX++;
		}
		else
		{
			//_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() <= 0)
			{
				_currentFrameX = 1;
			}
			_currentFrameX--;
		}

		_countTime = 0;
	}
}

void Enemy_Bunny::StopAnimation(UINT value)
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
