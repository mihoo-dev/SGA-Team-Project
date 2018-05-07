#include "stdafx.h"
#include "Enemy_Bear.h"


Enemy_Bear::Enemy_Bear()
	:_img(nullptr),
	_state(DEFAULT),
	_x(100),_y(247),
	_countTime(0),
	_frameSpeed(5),
	_moveSpeed(2),
	_isJump(FALSE),
	_jumpPower(0), _gravity(0),
	_time(0),
	_rndTime(200),
	_rndPattern(4),
	_hp(10),
	_isAttack(FALSE),
	_delay(0),
	_isDie(false),
	_hitTime(0)
{
}


Enemy_Bear::~Enemy_Bear()
{
}

HRESULT Enemy_Bear::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("bear_idle", "Chainsaw Bear_Idle.bmp", 972, 440, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_walk", "Chainsaw Bear_Walk.bmp", 1344, 444, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_back", "Chainsaw Bear_Back Walk.bmp", 1344, 444, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_run", "Chainsaw Bear_Run.bmp", 1302, 452, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_jump", "Chainsaw Bear_Jump.bmp", 1218, 468, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_roar", "Chainsaw Bear_Roar.bmp", 1692, 444, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_attack", "Chainsaw Bear_Swipe.bmp", 2640, 444, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bear_die", "Chainsaw Bear_Die.bmp", 2352, 500, 12, 2, true, RGB(255, 0, 255));

	SetState(RIGHT_WALK, 7);

	_x = x;
	_y = y;

	return S_OK;
}

void Enemy_Bear::release()
{
}

void Enemy_Bear::update()
{
	Move();
}

void Enemy_Bear::render()
{
	Draw();
}

void Enemy_Bear::Move()
{
	if (_state != LEFT_DIE && _state != RIGHT_DIE)
	{
		if (_x < 150)
		{
			_x = 150;
		}
		else if (_x > 700)
		{
			_x = 700;
		}

		//공격패턴이 진행되지 않고있고
		//뒷걸음질하고 있지 않으면 뒷걸음질한다
		if (_rndPattern == 4 &&
			_state != LEFT_BACK && _state != RIGHT_BACK)
		{
			//플레이어 오른쪽에 있으면
			if (_x + _img->getFrameWidth() / 2 > _playerX)
			{
				//SetFrameY(0)
				SetState(LEFT_BACK, 7);
			}
			//플레이어 왼쪽에 있으면
			else if (_x + _img->getFrameWidth() / 2 < _playerX)
			{
				//SetFrameY(1)
				SetState(RIGHT_BACK, 7);
			}
			_moveSpeed = 2.0f;
		}

		//뒷걸음과 그냥 걸음
		if (_state == LEFT_BACK) _x += _moveSpeed;
		else if (_state == RIGHT_BACK) _x -= _moveSpeed;
		else
		{
			if (_isRight) _x += _moveSpeed;
			else _x -= _moveSpeed;
		}

		if (_rndPattern == 4)
		{
			//일정 시간동안 뒷걸음질 하다가 랜덤 공격패턴 설정
			if (_time >= _rndTime)
			{
				//패턴이 진행되는 시간
				_rndTime = RND->getFromIntTo(200, 400);
				_rndPattern = RND->getInt(4);

				_time = -1;
			}
			_time++;
		}

		if (!_rndPattern) Pattern1();
		else if (_rndPattern == 1) Pattern2();
		else if (_rndPattern == 2) Pattern3();
		else if (_rndPattern == 3) Pattern4();

		if (_state == LEFT_ATTACK || _state == RIGHT_ATTACK)
		{
			_hitTime++;
			if (_hitTime >= 40)
			{
				if (_state == LEFT_ATTACK)
					_hitRc = RectMake(_rc.left + (_rc.right - _rc.left) / 2 - 100, _rc.bottom - 75, 100, 75);
				else if (_state == RIGHT_ATTACK)
					_hitRc = RectMake(_rc.left + (_rc.right - _rc.left) / 2, _rc.bottom - 75, 100, 75);
			}
		}
		else if (_state == LEFT_JUMP || _state == RIGHT_JUMP)
		{
			_hitTime++;
			if (_hitTime >= 30)
			{
				if (_state == LEFT_JUMP)
					_hitRc = RectMake(_rc.left, _rc.bottom, 150, 10);
				else if (_state == RIGHT_JUMP)
					_hitRc = RectMake(_rc.right - 150, _rc.bottom, 150, 10);
			}
		}
		else
		{
			_hitRc = RectMake(0, 0, 0, 0);
			_hitTime = 0;
		}

		if (!_isRight)
			_weaponRc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 + 16, _rc.top + 50, 40, 100);
		else
			_weaponRc = RectMakeCenter(_rc.right - (_rc.right - _rc.left) / 2 - 16, _rc.top + 50, 40, 100);
	}
	else
	{
		_hitRc = RectMake(0, 0, 0, 0);
		_weaponRc = RectMakeCenter(0, 0, 0, 0);
	}
	_countTime++;
	_rc = RectMake(_x + 10, _y + 5, _img->getFrameWidth() - 20, _img->getFrameHeight() - 10);

	if (_state == RIGHT_IDLE || _state == LEFT_IDLE ||
		_state == RIGHT_WALK || _state == LEFT_WALK ||
		_state == RIGHT_BACK || _state == LEFT_BACK ||
		_state == RIGHT_RUN || _state == LEFT_RUN ||
		_state == RIGHT_ROAR || _state == LEFT_ROAR)
		LoopAnimation();
	else
	{
		OneShotAnimation();
	}
}

void Enemy_Bear::Draw()
{
	if (_x + _img->getFrameWidth() > CAMERA->GetX() &&
		_x < CAMERA->GetX() + (CAMERA->GetRC().right - CAMERA->GetRC().left))
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		Rectangle(getMemDC(), _hitRc.left, _hitRc.top, _hitRc.right, _hitRc.bottom);
		Rectangle(getMemDC(), _weaponRc.left, _weaponRc.top, _weaponRc.right, _weaponRc.bottom);
		_img->frameRender(getMemDC(), _x, _y);
	}
}

void Enemy_Bear::Pattern1()
{
	if (_state != LEFT_RUN && _state != RIGHT_RUN)
	{
		_y -= 4;
		if (_x + _img->getFrameWidth() / 2 > _playerX)
		{
			SetState(LEFT_RUN, 5);
		}
		else if (_x + _img->getFrameWidth() / 2 < _playerX)
		{
			SetState(RIGHT_RUN, 5);
		}

		_moveSpeed = 4;
	}
	if (_x < 150 || _x > 700)
	{
		_y += 4;

		_rndTime = 100;
		_rndPattern = 4;

		_time = 0;
		return;
	}
	if (_time >= _rndTime)
	{
		_y += 4;

		//빽도하는 시간
		_rndTime = RND->getFromIntTo(100, 150);
		_rndPattern = 4;

		_time = 0;
		return;
	}
	_time++;

}

void Enemy_Bear::Pattern2()
{
	if (_state != RIGHT_ATTACK && _state != LEFT_ATTACK)
	{
		if (_state != LEFT_WALK && _state != RIGHT_WALK)
		{
			if (_x + _img->getFrameWidth() / 2 > _playerX)
			{
				SetState(LEFT_WALK, 7);
			}
			else if (_x + _img->getFrameWidth() / 2 < _playerX)
			{
				SetState(RIGHT_WALK, 7);
			}
			_moveSpeed = 2;
		}

		if (!_isAttack)
		{
			if (_time >= _rndTime)
			{
				//빽도하는 시간
				_rndTime = RND->getFromIntTo(100, 150);
				_rndPattern = 4;
				_isAttack = false;

				_time = 0;
				_delay = 0;

				return;
			}
			_time++;
		}
	}

	if (!_isAttack)
	{
		if (_rc.left < _playerRc.right &&
			_rc.top + 150 < _playerRc.bottom &&
			_rc.right > _playerRc.left &&
			_rc.bottom > _playerRc.top)
		{
			_saveX = _x;
			_isAttack = true;
			if (_x + _img->getFrameWidth() / 2 > _playerX)
			{
				_x -= 50;
				SetState(LEFT_ATTACK, 5);
			}
			else if (_x + _img->getFrameWidth() / 2 < _playerX)
			{
				_x -= 10;
				SetState(RIGHT_ATTACK, 5);
			}
			_moveSpeed = 0;
		}
	}
	else
	{
		_delay++;
		if (_delay > 200)
		{
			if (_x + _img->getFrameWidth() / 2 > _playerX)
			{
				SetState(LEFT_WALK, 7);
			}
			else if (_x + _img->getFrameWidth() / 2 < _playerX)
			{
				SetState(RIGHT_WALK, 7);
			}
			_moveSpeed = 2;

			_isAttack = false;
			_delay = 0;
		}
	}
}

void Enemy_Bear::Pattern3()
{
	if (_state != LEFT_ROAR)
	{
		_isRoar = true;
		if (_x + _img->getFrameWidth() / 2 > _playerX)
		{
			SetState(LEFT_ROAR);
			_moveSpeed = 0;
		}
	}
	else if (_state != RIGHT_ROAR)
	{
		_isRoar = true;
		if (_x + _img->getFrameWidth() / 2 < _playerX)
		{
			SetState(RIGHT_ROAR);
			_moveSpeed = 0;
		}
	}

	if (_time >= _rndTime)
	{
		_rndTime = RND->getFromIntTo(100, 150);
		_rndPattern = 4;
		_time = 0;
		_isRoar = false;
		return;
	}
	++_time;
}

void Enemy_Bear::Pattern4()
{
	if (!_isJump && _state != LEFT_JUMP && _state != RIGHT_JUMP)
	{
		if (_x + _img->getFrameWidth() / 2 > _playerX)
		{
			SetState(LEFT_JUMP, 8);
		}
		if (_x + _img->getFrameWidth() / 2 < _playerX)
		{
			SetState(RIGHT_JUMP, 8);
		}
		_moveSpeed = 3;

		_isJump = true;
		_jumpPower = 12.0f;
		_gravity = 0.5f;
	}

	if (_isJump)
	{
		Jump();
	}
	else
	{
		_rndTime = RND->getFromIntTo(100, 150);
		_rndPattern = 4;
		_time = 0;

		return;
	}
}

void Enemy_Bear::Jump()
{
	_y -= _jumpPower;
	_jumpPower -= _gravity;

	if (_y > 225)
	{
		_isJump = false;
		_y = 225;
	}
}

void Enemy_Bear::Die()
{
	if (_state != LEFT_DIE && _state != RIGHT_DIE)
	{
		SetState(RIGHT_DIE, 8);
		_saveX = _x;
		_y -= 25;
	}
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

void Enemy_Bear::OneShotAnimation()
{
	if (_countTime >= _frameSpeed)
	{
		if (_isRight)
		{
			_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() >= _img->getMaxFrameX())
			{
				_currentFrameX = _img->getMaxFrameX() - 1;
				if (_isAttack)
				{
					_x = _saveX;
				}
				_rndTime = RND->getFromIntTo(100, 150);
				_rndPattern = RND->getInt(4);
				_time = 0;
			}
			_currentFrameX++;
		}
		else
		{
			_img->setFrameX(_currentFrameX);
			if (_img->getFrameX() <= 0)
			{
				_currentFrameX = 1;
				if (_isAttack)
				{
					_x = _saveX;
				}
				_rndTime = RND->getFromIntTo(100, 150);
				_rndPattern = RND->getInt(4);
				_time = 0;
			}
			_currentFrameX--;
		}

		_countTime = 0;
	}
}

