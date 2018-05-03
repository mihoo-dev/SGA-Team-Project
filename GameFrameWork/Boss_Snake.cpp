#include "stdafx.h"
#include "Boss_Snake.h"


Boss_Snake::Boss_Snake()
	: _img(IMAGEMANAGER->findImage("BOSS_SNAKE"))
	, _startX(50), _endX(750)
	, _x(_endX), _y(418+200)
	, _state(SNAKE_LEFT_IDLE)
	, _direction(SNAKE_LEFT)
	, _count(0), _isPlay(false)
	, _attack(0), _attackCount(0)
{
}


Boss_Snake::~Boss_Snake()
{
}

HRESULT Boss_Snake::init()
{
	int leftIdle[] = { 76, 75, 74, 73, 72, 71, 70, 69 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_LEFT_IDLE", "BOSS_SNAKE", leftIdle, 8, 5, true);
	
	int rightIdle[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_RIGHT_IDLE", "BOSS_SNAKE", rightIdle, 8, 5, true);
	
	int leftMove[] = { 87, 86, 85, 84, 83, 82, 81, 80 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_LEFT_MOVE", "BOSS_SNAKE", leftMove, 8, 8, true);

	int rightMove[] = { 11, 12, 13, 14, 15, 16, 17, 18 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_RIGHT_MOVE", "BOSS_SNAKE", rightMove, 8, 8, true);

	int leftCloud[] = { 98, 97, 96, 95, 94, 93, 92, 91, 90, 89 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_LEFT_CLOUD", "BOSS_SNAKE", leftCloud, 10, 8, false);

	int rightCloud[] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_RIGHT_CLOUD", "BOSS_SNAKE", rightCloud, 10, 8, false);

	int leftPoison[] = { 109, 108, 107, 106, 105, 104, 103, 102, 104, 103, 102, 101, 100, 99 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_LEFT_POISON", "BOSS_SNAKE", leftPoison, 14, 8, false);

	int rightPoison[] = { 33, 34, 35, 36, 37, 38, 39, 40, 38, 39, 40, 41, 42, 43 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_RIGHT_POISON", "BOSS_SNAKE", rightPoison, 14, 8, false);

	int leftDamaged[] = { 120, 119, 118, 117 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_LEFT_DAMAGED", "BOSS_SNAKE", leftDamaged, 4, 8, false);

	int rightDamaged[] = { 44, 45, 46, 47 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_RIGHT_DAMAGED", "BOSS_SNAKE", rightDamaged, 4, 8, false);

	int leftDie[] = { 131, 130, 129, 128, 127, 126, 125, 124, 123, 122 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_LEFT_DIE", "BOSS_SNAKE", leftDie, 10, 8, false);

	int rightDie[] = { 55, 56, 57, 58, 59, 60, 61, 62, 63, 64 };
	KEYANIMANAGER->addArrayFrameAnimation("SNAKE_RIGHT_DIE", "BOSS_SNAKE", rightDie, 10, 8, false);

	_motion = KEYANIMANAGER->findAnimation("SNAKE_LEFT_IDLE");
	_motion->start();

	return S_OK;
}

void Boss_Snake::release()
{
}

void Boss_Snake::update()
{
	Operation();
	CheckState();
	AttackRC();
	DamageRC();
	Die();

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_state = SNAKE_LEFT_CLOUD;
	}
	if (KEYMANAGER->isOnceKeyDown('O')) PlayDamage();
}

void Boss_Snake::render()
{
	Rectangle(getMemDC(), _attackRC.left, _attackRC.top, _attackRC.right, _attackRC.bottom);
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	_img->aniRender(getMemDC()
		, _x - _img->getFrameWidth() / 2
		, _y - _img->getFrameHeight() / 2
		, _motion);
}

void Boss_Snake::Set(float x, float y)
{
	_x = x;
	_y = y;
	_state = SNAKE_WAIT_PLAYER;
}

void Boss_Snake::CheckState()
{
	switch (_state)
	{
	case SNAKE_WAIT_PLAYER:

		break;

	case SNAKE_LEFT_IDLE:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_LEFT_IDLE");
		_direction = SNAKE_LEFT;
		if (_motion->isPlay() == false) _motion->start();
	break;

	case SNAKE_RIGHT_IDLE:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_RIGHT_IDLE");
		_direction = SNAKE_RIGHT;
		if (_motion->isPlay() == false) _motion->start();
	break;

	case SNAKE_LEFT_MOVE:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_LEFT_MOVE");
		_direction = SNAKE_LEFT;

		if (_motion->isPlay() == false) _motion->start();
		Move("LEFT");
		if (_x < _startX)
		{
			_motion->stop();
			_x = _startX;
			_state = SNAKE_RIGHT_IDLE;
		}
	break;

	case SNAKE_RIGHT_MOVE:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_RIGHT_MOVE");
		_direction = SNAKE_RIGHT;

		if (_motion->isPlay() == false) _motion->start();
		Move("RIGHT");
		if (_x > _endX)
		{
			_motion->stop();
			_x = _endX;
			_state = SNAKE_LEFT_IDLE;
		}
	break;

	case SNAKE_LEFT_CLOUD:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_LEFT_CLOUD");
		_direction = SNAKE_LEFT;

		if (_motion->isPlay() == false)
		{
			if (!_isPlay)
			{
				_motion->start();
				_isPlay = true;
				_attack = 2;
			}
			else
			{
				_state = SNAKE_LEFT_MOVE;
				_isPlay = false;
			}
		}
		break;

	case SNAKE_RIGHT_CLOUD:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_RIGHT_CLOUD");
		_direction = SNAKE_RIGHT;

		if (_motion->isPlay() == false)
		{
			if (!_isPlay)
			{
				_motion->start();
				_isPlay = true;
				_attack = 2;
			}
			else
			{
				_state = SNAKE_RIGHT_MOVE;
				_isPlay = false;
			}
		}
		break;
	case SNAKE_LEFT_POISON:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_LEFT_POISON");
		_direction = SNAKE_LEFT;

		if (_motion->isPlay() == false)
		{
			if (!_isPlay)
			{
				_motion->start();
				_isPlay = true;
			}
			else
			{
				_attack = 1;
				for (int ii = 0; ii < 11; ++ii)
				{			
					EFFECTMANAGER->play("EFFECT_POISON", 90 * (ii + 1), 368);
				}
				_state = SNAKE_LEFT_IDLE;
				_isPlay = false;
			}
		}
		break;
	case SNAKE_RIGHT_POISON:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_RIGHT_POISON");
		_direction = SNAKE_RIGHT;

		if (_motion->isPlay() == false)
		{
			if (!_isPlay)
			{
				_motion->start();
				_isPlay = true;
			}
			else
			{
				_attack = 1;
				for (int ii = 0; ii < 11; ++ii)
				{
					EFFECTMANAGER->play("EFFECT_POISON", 90 * (ii + 1), 368);
				}
				_state = SNAKE_RIGHT_IDLE;
				_isPlay = false;
			}
		}
		break;
	case SNAKE_LEFT_DAMAGED:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_LEFT_DAMAGED");
		_direction = SNAKE_LEFT;

		if (_motion->isPlay() == false)
		{
			if (!_isPlay)
			{
				_motion->start();
				_isPlay = true;
			}
			else
			{
				_state = SNAKE_LEFT_CLOUD;
				_isPlay = false;
			}
		}
		break;
	case SNAKE_RIGHT_DAMAGED:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_RIGHT_DAMAGED");
		_direction = SNAKE_RIGHT;

		if (_motion->isPlay() == false)
		{
			if (!_isPlay)
			{
				_motion->start();
				_isPlay = true;
			}
			else
			{
				_state = SNAKE_RIGHT_CLOUD;
				_isPlay = false;

			}
		}
		break;

	case SNAKE_LEFT_DIE:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_LEFT_DIE");
		if (_motion->isPlay() == false)
		{
			if (!_isPlay)
			{
				_motion->start();
				_isPlay = true;
			}
		}
		break;

	case SNAKE_RIGHT_DIE:
		_motion = KEYANIMANAGER->findAnimation("SNAKE_RIGHT_DIE");
		if (_motion->isPlay() == false)
		{
			if (!_isPlay)
			{
				_motion->start();
				_isPlay = true;
			}
		}
		break;
	}
}

void Boss_Snake::Operation()
{
	if (_state == SNAKE_LEFT_IDLE || _state == SNAKE_RIGHT_IDLE)	_count++;

	if (_count > 200)
	{
		if (_direction == SNAKE_RIGHT) _state = SNAKE_RIGHT_POISON;
		else _state = SNAKE_LEFT_POISON;
		_count = 0;
	}
	
}

void Boss_Snake::Move(string direction)
{
	if (direction == "LEFT")
	{
		_x -= 4;
	}
	else if (direction == "RIGHT")
	{
		_x += 4;
	}
}

void Boss_Snake::Die()
{
	if (_HP > 0) return;

	switch (_direction)
	{
		case SNAKE_LEFT:
			_state = SNAKE_LEFT_DIE;
		break;
		case SNAKE_RIGHT:
			_state = SNAKE_RIGHT_DIE;
		break;
	}

}

RECT Boss_Snake::AttackRC()
{
	//RECT temp = { 0,0,0,0 };
	if (_attack == 0) _attackRC = { 0,0,0,0 };
	else if (_attack == 1)
	{
		_attackRC = { 90, 318, 1030, 418 };
		_attackCount++;
		
		if (_attackCount > 15)
		{
			_attackCount = 0;
			_attack = 0;
		}	
	}
	else if (_attack == 2)
	{
		_attackCount++;
		if (_attackCount > 15)
		{
			switch (_direction)
			{
			case SNAKE_LEFT:
				_attackRC = { _rc.left - 80, _rc.top - 40, _rc.right + 60, _rc.bottom + 30 };
			break;
			case SNAKE_RIGHT:
				_attackRC = { _rc.left - 60, _rc.top - 40, _rc.right + 80, _rc.bottom + 30 };
			break;
			}
		}
		if (_attackCount > 45)
		{
			_attackCount = 0;
			_attack = 0;
		}
	}

	return _attackRC;
}

RECT Boss_Snake::DamageRC()
{
	if (_direction == SNAKE_RIGHT)	_rc = RectMakeCenter(_x + 15, _y, 110, 80);
	else 	_rc = RectMakeCenter(_x - 15, _y, 110, 80);

	return _rc;
}

void Boss_Snake::PlayDamage()
{
	_motion->stop();			//이전 애니메이션 일시정지
	_isPlay = false;			//애니메이션 플레이 중 아님
	
	if (_direction == SNAKE_LEFT)			_state = SNAKE_LEFT_DAMAGED;
	else if (_direction == SNAKE_RIGHT)		_state = SNAKE_RIGHT_DAMAGED;
}
