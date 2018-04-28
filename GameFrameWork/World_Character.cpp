#include "stdafx.h"
#include "World_Character.h"


World_Character::World_Character()
	: _x(1610), _y(820)
	, _angle(PI / 2 * 3), _img(nullptr)
	, _motion(nullptr), _state(WORLD_SOUTH_IDLE)
	, _frameX(0), _frameY(0)
	, _right(0), _left(0), _up(0), _down(0)
	, _collisionLeft(1), _collisionRight(1)
	, _collisionUp(1), _collisionDown(1)
{
}


World_Character::~World_Character()
{
}

HRESULT World_Character::init()
{

	_img = IMAGEMANAGER->findImage("WORLD_FINN");

	return S_OK;
}

void World_Character::release()
{
}

void World_Character::update()
{
	KEYANIMANAGER->update();

	move();
	checkDirection();
	checkPixel();
	changeState();
	setCamera();

	_rc = RectMakeCenter(_x, _y + 16, 32, 20);
}

void World_Character::render(HDC hdc)
{
	//캐릭터 렌더
	if (_state == WORLD_EAST_IDLE || _state == WORLD_WEST_IDLE
		|| _state == WORLD_SOUTH_IDLE || _state == WORLD_NORTH_IDLE
		|| _state == WORLD_SOUTH_EAST_IDLE || _state == WORLD_SOUTH_WEST_IDLE
		|| _state == WORLD_NORTH_WEST_IDLE || _state == WORLD_NORTH_EAST_IDLE)
	{
		_img->frameRender(hdc
			, _x - _img->getFrameWidth() / 2
			, _y - _img->getFrameHeight() / 2
			, _frameX
			, _frameY);
	}
	else _img->aniRender(hdc
		, _x - _img->getFrameWidth() / 2
		, _y - _img->getFrameHeight() / 2
		, _motion);

	Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void World_Character::setImage(string imageKey)
{
	_img = IMAGEMANAGER->findImage(imageKey);
}

void World_Character::checkDirection()
{
	//키 입력 시 방향 입력 (키입력 && 중복입력 예외처리)
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !_left)	_right = true;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !_right)	_left = true;
	if (KEYMANAGER->isStayKeyDown(VK_UP) && !_down)		_up = true;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !_up)		_down = true;

	//키 해제 시 방향 해제
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))		_right = false;
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))		_left = false;
	if (KEYMANAGER->isOnceKeyUp(VK_UP))			_up = false;
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))		_down = false;

	//모든 키 해제 시 각도에 따른 IDLE 상태 체크
	if (!_right && !_left && !_up && !_down)
	{
		_frameY = 0;

		if (_angle == (PI / 4) * 6)
		{
			_state = WORLD_SOUTH_IDLE;
			_frameX = 0;
		}

		else if (_angle == (PI / 4) * 7)
		{
			_state = WORLD_SOUTH_EAST_IDLE;
			_frameX = 1;
		}

		else if (_angle == 0)
		{
			_state = WORLD_EAST_IDLE;
			_frameX = 2;
		}
		else if (_angle == (PI / 4) * 1)
		{
			_state = WORLD_NORTH_EAST_IDLE;
			_frameX = 3;
		}
		else if (_angle == (PI / 4) * 2)
		{
			_state = WORLD_NORTH_IDLE;
			_frameX = 4;
		}
		else if (_angle == (PI / 4) * 3)
		{
			_state = WORLD_NORTH_WEST_IDLE;
			_frameX = 5;
		}
		else if (_angle == (PI / 4) * 4)
		{
			_state = WORLD_WEST_IDLE;
			_frameX = 6;
		}
		else if (_angle == (PI / 4) * 5)
		{
			_state = WORLD_WEST_IDLE;
			_frameX = 7;
		}
	}
}

void World_Character::checkPixel()
{
	image* pixelMap = IMAGEMANAGER->addImage("WORLD_MAP_PIXEL", "WORLD_MAP_PIXEL.bmp", 2793, 2111, false, NULL);

	COLORREF RIGHT = GetPixel(pixelMap->getMemDC(), _rc.right, (_rc.top + _rc.bottom) / 2);
	COLORREF LEFT = GetPixel(pixelMap->getMemDC(), _rc.left, (_rc.top + _rc.bottom) / 2);
	COLORREF UP = GetPixel(pixelMap->getMemDC(), (_rc.right + _rc.left) / 2, _rc.top);
	COLORREF DOWN = GetPixel(pixelMap->getMemDC(), (_rc.right + _rc.left) / 2, _rc.bottom);

	if (RIGHT == RGB(255, 0, 0))
	{
		_collisionRight = 0;
	}
	else _collisionRight = 1;
	if (LEFT == RGB(255, 0, 0))
	{
		_collisionLeft = 0;
	}
	else _collisionLeft = 1;
	if (UP == RGB(255, 0, 0))
	{
		_collisionUp = 0;
	}
	else _collisionUp = 1;
	if (DOWN == RGB(255, 0, 0))
	{
		_collisionDown = 0;
	}
	else _collisionDown = 1;
}

void World_Character::changeState()
{
	//해당 방향에 대한 각도, 상태, 모션 변경
	if (_right && !_left && !_up && !_down)
	{
		_angle = 0;
		_state = WORLD_EAST_MOVE;
		_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_EAST_MOVE");
	}
	else if (!_right && _left && !_up && !_down)
	{
		_angle = (PI / 4) * 4;
		_state = WORLD_WEST_MOVE;
		_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_WEST_MOVE");
	}
	else if (!_right && !_left && _up && !_down)
	{
		_angle = (PI / 4) * 2;
		_state = WORLD_NORTH_MOVE;
		_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_NORTH_MOVE");
	}
	else if (!_right && !_left && !_up && _down)
	{
		_angle = (PI / 4) * 6;
		_state = WORLD_SOUTH_MOVE;
		_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_SOUTH_MOVE");
	}
	else if (_right && !_left && _up && !_down)
	{
		_angle = (PI / 4);
		_state = WORLD_NORTH_EAST_MOVE;
		_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_NORTH_EAST_MOVE");
	}
	else if (_right && !_left && !_up && _down)
	{
		_angle = PI / 4 * 7;
		_state = WORLD_SOUTH_EAST_MOVE;
		_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_SOUTH_EAST_MOVE");
	}
	else if (!_right && _left && _up && !_down)
	{
		_angle = PI / 4 * 3;
		_state = WORLD_NORTH_WEST_MOVE;
		_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_NORTH_WEST_MOVE");
	}
	else if (!_right && _left && !_up && _down)
	{
		_angle = PI / 4 * 5;
		_state = WORLD_SOUTH_WEST_MOVE;
		_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_SOUTH_WEST_MOVE");
	}
}

void World_Character::setCamera()
{
	CAMERA->update(_x, _y, 2, true);
}

void World_Character::move()
{
	if (!_right && !_left && !_up && !_down) return;

	if (_right)	_x += cosf(_angle) * WORLD_SPEED * _collisionRight;
	if (_left)	_x += cosf(_angle) * WORLD_SPEED * _collisionLeft;
	if (_up)		_y += -sinf(_angle) * WORLD_SPEED * _collisionUp;
	if (_down)	_y += -sinf(_angle) * WORLD_SPEED * _collisionDown;
}
