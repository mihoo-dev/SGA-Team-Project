#include "stdafx.h"
#include "World_Character.h"
#include "World_Bridge.h"


World_Character::World_Character()
	: _x(1610), _y(820)
	, _angle(PI / 2 * 3), _img(nullptr)
	, _motion(nullptr), _state(WORLD_SOUTH_IDLE)
	, _frameX(0), _frameY(0)
	, _right(0), _left(0), _up(0), _down(0)
	, _collisionLeft(1), _collisionRight(1)
	, _collisionUp(1), _collisionDown(1)
	, _followTrace(true), _traceIndex(SIZEOFTRACE)
	, _bridgeState(NOTHING_TO_DO)
	, _jakeMotion(KEYANIMANAGER->findAnimation("WORLD_JAKE_WEST_MOVE"))
	, _canMakeBridge(false), _meetDog(true)
	, _pressX(false), _Xframe(0), _Xcount(0)
	, _colorBridge(RGB(0,0,255)), _colorStore(RGB(1,1,1)), _colorGraveyard(RGB(2,2,2))
{
}


World_Character::~World_Character()
{
}

HRESULT World_Character::init()
{
	for (int ii = 0; ii <= SIZEOFTRACE; ++ii)
	{
		_traceFinn.x = _x;
		_traceFinn.y = _y - (SIZEOFTRACE - ii) * 2;
		_traceFinn.state = WORLD_SOUTH_IDLE;
		_traceFinn.idleFrame = 0;

		_vTrace.push_back(_traceFinn);
	}

	_img = IMAGEMANAGER->findImage("WORLD_FINN");
	_jakeImg = IMAGEMANAGER->findImage("WORLD_JAKE");

	return S_OK;
}

void World_Character::release()
{
	SAFE_DELETE(_bridge);
	SAFE_RELEASE(_img);
	SAFE_RELEASE(_jakeImg);
}

void World_Character::update()
{
	if (_bridgeState == NOTHING_TO_DO)
	{
		Move();
		CheckDirection();
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			switch (_buttonState)
			{
			case NO_PRESS:
				break;
			case GO_STORE:
				SCENEMANAGER->changeScene("StoreScene", "LoadingScene");
			break;
			case MAKE_BRIDGE:
				MakeBridge();
			break;
			default:
				break;
			}
		}
	}

	CheckPixel();
	ChangeState();
	SetCamera();
	CheckTrace();
	BridgeOperation();	
	button();


	_rc = RectMakeCenter(_x, _y + 16, 32, 20);
}

void World_Character::render(HDC hdc)
{
	//JAKE 렌더
	if (_bridgeState == NOTHING_TO_DO)	DrawJake(hdc);

	//FINN 렌더
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

	if (_bridgeState == JAKE_HORIZONTAL_MOVE || _bridgeState == JAKE_VERTICAL_MOVE)
	{
		_jakeImg->aniRender(hdc
			, _jakeX - _img->getFrameWidth() / 2
			, _jakeY - _img->getFrameHeight() / 2
			, _jakeMotion);
	}

	if (_pressX && _bridgeState == NOTHING_TO_DO)
	{
		IMAGEMANAGER->findImage("PRESS_X")->frameRender(hdc, _x - 14, _y - 60 - 14, _Xframe, 0);
	}

	CheckStatus(hdc);
	//Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void World_Character::CheckDirection()
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

void World_Character::CheckPixel()
{
	image* pixelMap = IMAGEMANAGER->addImage("WORLD_MAP_PIXEL", "WORLD_MAP_PIXEL.bmp", 2793, 2111, false, NULL);

	COLORREF RIGHT = GetPixel(pixelMap->getMemDC(), _rc.right, (_rc.top + _rc.bottom) / 2);
	COLORREF LEFT = GetPixel(pixelMap->getMemDC(), _rc.left, (_rc.top + _rc.bottom) / 2);
	COLORREF UP = GetPixel(pixelMap->getMemDC(), (_rc.right + _rc.left) / 2, _rc.top);
	COLORREF DOWN = GetPixel(pixelMap->getMemDC(), (_rc.right + _rc.left) / 2, _rc.bottom);

	//이동에 관한 픽셀 체크
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


	//다리 만들기
	if (RIGHT == _colorBridge || LEFT == _colorBridge || UP == _colorBridge || DOWN == _colorBridge)
	{
		if (_meetDog)
		{
			_canMakeBridge = true;
			_pressX = true;
			_buttonState = MAKE_BRIDGE;
		}
	}
	//상점
	else if (RIGHT == _colorStore || LEFT == _colorStore || UP == _colorStore || DOWN == _colorStore)
	{
		_pressX = true;
		_buttonState = GO_STORE;
	}

	//그레이브야드
	else if (RIGHT == _colorGraveyard || LEFT == _colorGraveyard || UP == _colorGraveyard || DOWN == _colorGraveyard)
	{
		_pressX = true;
		_buttonState = GO_GRAVEYARD;
	}
	else
	{
		_canMakeBridge = false;
		_pressX = false;
		_buttonState = NO_PRESS;
	}
}

void World_Character::ChangeState()
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

void World_Character::SetCamera()
{
	CAMERA->update(_x, _y, 2, true);
}

void World_Character::Move()
{
	if (!_right && !_left && !_up && !_down) return;

	if (_right)	_x += cosf(_angle) * WORLD_SPEED * _collisionRight;
	if (_left)	_x += cosf(_angle) * WORLD_SPEED * _collisionLeft;
	if (_up)	_y += -sinf(_angle) * WORLD_SPEED * _collisionUp;
	if (_down)	_y += -sinf(_angle) * WORLD_SPEED * _collisionDown;

	//FINN의 움직임을 벡터에 저장
	SaveTrace(_traceIndex);
	
}

void World_Character::CheckTrace()
{
	if (_collisionRight + _collisionLeft + _collisionUp + _collisionDown <= 2)
		_followTrace = false;
	else _followTrace = true;
}

void World_Character::SaveTrace(int index)
{
	if (!_followTrace) return;

	_vTrace[_traceIndex].x = (int)_x;
	_vTrace[_traceIndex].y = (int)_y;
	_vTrace[_traceIndex].state = _state;

	//상태에 따른 모션 저장
	switch (_state)
	{
	case WORLD_EAST_MOVE:
		_vTrace[_traceIndex].motion = KEYANIMANAGER->findAnimation("WORLD_JAKE_EAST_MOVE");
		_vTrace[_traceIndex].idleFrame = 2;
	break;
	case WORLD_WEST_MOVE:
		_vTrace[_traceIndex].motion = KEYANIMANAGER->findAnimation("WORLD_JAKE_WEST_MOVE");
		_vTrace[_traceIndex].idleFrame = 6;
	break;
	case WORLD_NORTH_MOVE:
		_vTrace[_traceIndex].motion = KEYANIMANAGER->findAnimation("WORLD_JAKE_NORTH_MOVE");
		_vTrace[_traceIndex].idleFrame = 4;
	break;
	case WORLD_SOUTH_MOVE:
		_vTrace[_traceIndex].motion = KEYANIMANAGER->findAnimation("WORLD_JAKE_SOUTH_MOVE");
		_vTrace[_traceIndex].idleFrame = 0;
	break;
	case WORLD_NORTH_EAST_MOVE:
		_vTrace[_traceIndex].motion = KEYANIMANAGER->findAnimation("WORLD_JAKE_NORTH_EAST_MOVE");
		_vTrace[_traceIndex].idleFrame = 3;
	break;
	case WORLD_NORTH_WEST_MOVE:
		_vTrace[_traceIndex].motion = KEYANIMANAGER->findAnimation("WORLD_JAKE_NORTH_WEST_MOVE");
		_vTrace[_traceIndex].idleFrame = 5;
	break;
	case WORLD_SOUTH_EAST_MOVE:
		_vTrace[_traceIndex].motion = KEYANIMANAGER->findAnimation("WORLD_JAKE_SOUTH_EAST_MOVE");
		_vTrace[_traceIndex].idleFrame = 1;
	break;
	case WORLD_SOUTH_WEST_MOVE:
		_vTrace[_traceIndex].motion = KEYANIMANAGER->findAnimation("WORLD_JAKE_SOUTH_WEST_MOVE");
		_vTrace[_traceIndex].idleFrame = 7;
	break;
	}

	_traceIndex++;
	if (_traceIndex > SIZEOFTRACE) _traceIndex = 0;
}

void World_Character::DrawJake(HDC hdc)
{
	//인덱스 값 셋팅
	int index = (_traceIndex + 1) % (SIZEOFTRACE + 1);

	_jakeX = _vTrace[index].x;
	_jakeY = _vTrace[index].y;

	if (_state == WORLD_EAST_IDLE || _state == WORLD_WEST_IDLE
		|| _state == WORLD_SOUTH_IDLE || _state == WORLD_NORTH_IDLE
		|| _state == WORLD_SOUTH_EAST_IDLE || _state == WORLD_SOUTH_WEST_IDLE
		|| _state == WORLD_NORTH_WEST_IDLE || _state == WORLD_NORTH_EAST_IDLE)
	{
			_jakeImg->frameRender(hdc
				, _jakeX - _img->getFrameWidth() / 2
				, _jakeY - _img->getFrameHeight() / 2
				, _vTrace[index].idleFrame, 0);
	}

	else _jakeImg->aniRender(hdc
		, _jakeX - _img->getFrameWidth() / 2
		, _jakeY - _img->getFrameHeight() / 2
		, _motion);
}

void World_Character::MakeBridge()
{
	if (_canMakeBridge == false) return;

	_bridgeState = JAKE_HORIZONTAL_MOVE;
}

void World_Character::BridgeOperation()
{
	switch (_bridgeState)
	{
	//제이크 수평 이동
	case JAKE_HORIZONTAL_MOVE:
		
		//제이크의 위치에 따라 다리 만드는 방향 결정
		if (_jakeY <= (BRIDGETOPSTART + BRIDGEBOTTOMSTART) / 2) _bridge->SetBridgeDirection(0);
		else _bridge->SetBridgeDirection(1);

		//제이크의 X 좌표가 다리 중심 좌표보다 동쪽에 있을 때
		if (_jakeX > BRIDGEX)
		{
			//제이크의 모션은 서쪽 이동아닐 경우 변경하고 좌로 이동
			if (_jakeMotion != KEYANIMANAGER->findAnimation("WORLD_JAKE_WEST_MOVE")) {
				_jakeMotion = KEYANIMANAGER->findAnimation("WORLD_JAKE_WEST_MOVE");
			}
			_jakeX -= 2;
			

			//목표 점에 도달하는 경우
			if (_jakeX <= BRIDGEX)
			{
				//중심점 맞추고 다음 상태로 넘긴다
				_jakeX = BRIDGEX;
				_bridgeState = JAKE_VERTICAL_MOVE;
			}
		}
		//제이크의 X 좌표가 다리 중심 좌표보다 서쪽에 있을 때
		else if (_jakeX < BRIDGEX)
		{
			//제이크의 모션은 동쪽 이동으로 바꾸고 좌로 이동
			if (_jakeMotion != KEYANIMANAGER->findAnimation("WORLD_JAKE_EAST_MOVE")) {
				_jakeMotion = KEYANIMANAGER->findAnimation("WORLD_JAKE_EAST_MOVE");
			}
			_jakeX += 2;
			
			//목표 점에 도달하는 경우
			if (_jakeX >= BRIDGEX)
			{
				//중심점 맞추고 다음 상태로 넘긴다
				_jakeX = BRIDGEX;
				_bridgeState = JAKE_VERTICAL_MOVE;
			}
		}
		else _bridgeState = JAKE_VERTICAL_MOVE;
	break;

	//제이크 수직 이동
	case JAKE_VERTICAL_MOVE:
		if (_bridge->GetBridgeDirection() == 0)
		{
			//제이크의 모션이 남쪽 이동이 아닌경우 변경해주고 남으로 이동
			if (_jakeMotion != KEYANIMANAGER->findAnimation("WORLD_JAKE_SOUTH_MOVE")) {
				_jakeMotion = KEYANIMANAGER->findAnimation("WORLD_JAKE_SOUTH_MOVE");
			}
			_jakeY += 2;

			if (_jakeY >= BRIDGETOPSTART)
			{
				_jakeY = BRIDGETOPSTART;
				_bridge->SetFrameX(0);
				if (_bridge->GetBridgeDirection() == 0) _bridge->SetFrameY(0);
				else _bridge->SetFrameY(1);
				_bridgeState = JAKE_MAKE_BRIDGE;
			}
		}
		else
		{
			//제이크의 모션이 북쪽 이동이 아닌경우 변경해주고 북으로 이동
			if (_jakeMotion != KEYANIMANAGER->findAnimation("WORLD_JAKE_NORTH_MOVE")) {
				_jakeMotion = KEYANIMANAGER->findAnimation("WORLD_JAKE_NORTH_MOVE");
			}
			_jakeY -= 2;

			if (_jakeY <= BRIDGEBOTTOMSTART)
			{
				_jakeY = BRIDGEBOTTOMSTART;
				_bridge->SetFrameX(0);
				if (_bridge->GetBridgeDirection() == 0) _bridge->SetFrameY(0);
				else _bridge->SetFrameY(1);
				_bridgeState = JAKE_MAKE_BRIDGE;
			}
		}
		break;
	
	//다리 만들기
	case JAKE_MAKE_BRIDGE:
		_bridge->MakeBridge();
	break;

	//핀 수평 이동
	case FINN_HORIZONTAL_MOVE:
		if (_x > BRIDGEX)
		{
			if (_state != WORLD_WEST_MOVE) _state = WORLD_WEST_MOVE;
			if (_motion != KEYANIMANAGER->findAnimation("WORLD_FINN_WEST_MOVE")) {
				_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_WEST_MOVE");
			}
			_x -= 2;
			if (_x <= BRIDGEX)
			{
				_x = BRIDGEX;
				_bridgeState = FINN_VERTICAL_MOVE;
			}
		}
		else if (_x < BRIDGEX)
		{
			if (_state != WORLD_EAST_MOVE) _state = WORLD_EAST_MOVE;
			if (_motion != KEYANIMANAGER->findAnimation("WORLD_FINN_EAST_MOVE")) {
				_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_EAST_MOVE");
			}
			_x += 2;
			if (_x >= BRIDGEX)
			{
				_x = BRIDGEX;
				_bridgeState = FINN_VERTICAL_MOVE;
			}
		}
		else _bridgeState = FINN_VERTICAL_MOVE;
	break;

	case FINN_VERTICAL_MOVE:
		if (_bridge->GetBridgeDirection() == 0)
		{
			if (_state != WORLD_SOUTH_MOVE) _state = WORLD_SOUTH_MOVE;
			if (_motion != KEYANIMANAGER->findAnimation("WORLD_FINN_SOUTH_MOVE")) {
				_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_SOUTH_MOVE");
			}
			_y += 2;
			if (_y >= BRIDGETOPEND)
			{
				_y = BRIDGETOPEND;
				for (int ii = SIZEOFTRACE; ii >= 0; --ii)
				{
					_vTrace[ii].x = _x;
					_vTrace[ii].y = _y - (SIZEOFTRACE - ii) * 2;
					_vTrace[ii].idleFrame = 0;
					_vTrace[ii].motion = KEYANIMANAGER->findAnimation("WORLD_JAKE_SOUTH_MOVE");
				}
				_traceIndex = SIZEOFTRACE;
				_bridgeState = JAKE_REMOVE_BRIDGE;
				_state = WORLD_SOUTH_IDLE;
				_frameX = 0;
				_angle = (PI / 4) * 6;
			}
		}
		else
		{
			if (_state != WORLD_NORTH_MOVE) _state = WORLD_NORTH_MOVE;
			if (_motion != KEYANIMANAGER->findAnimation("WORLD_FINN_NORTH_MOVE")) {
				_motion = KEYANIMANAGER->findAnimation("WORLD_FINN_NORTH_MOVE");
			}
			_y -= 2;
			if (_y <= BRIDGEBOTTOMEND)
			{
				_y = BRIDGEBOTTOMEND;
				for (int ii = SIZEOFTRACE; ii >= 0; --ii)
				{
					_vTrace[ii].x = _x;
					_vTrace[ii].y = _y + (SIZEOFTRACE - ii) * 2;
					_vTrace[ii].idleFrame = 4;
					_vTrace[ii].motion = KEYANIMANAGER->findAnimation("WORLD_JAKE_NORTH_MOVE");
				}
				_traceIndex = SIZEOFTRACE;			
				_bridgeState = JAKE_REMOVE_BRIDGE;
				_state = WORLD_NORTH_IDLE;
				_frameX = 4;
				_angle = (PI / 4) * 2;
			}
		}
	break;

	case JAKE_REMOVE_BRIDGE:
		_bridge->RemoveBridge();
	break;

	case JAKE_SET_POSITION:
		if (_bridge->GetBridgeDirection() == 0)	_jakeY = _y - 42.0f;
		else _jakeY = _y + 42.0f;
		_bridgeState = NOTHING_TO_DO;
	break;
	}
}

void World_Character::button()
{
	if (_pressX)
	{
		_Xcount++;
		if (_Xcount > 20)
		{
			_Xcount = 0;
			_Xframe++;
		}
		if (_Xframe > 1) _Xframe = 0;
	}
}

void World_Character::CheckStatus(HDC hdc)
{
	char status[128];
	sprintf_s(status, "canMakeBridge : %d, distance : %0.f"
		, _canMakeBridge, getDistance(_x,_y,_jakeX,_jakeY));
	TextOut(hdc, CAMERA->GetX(), CAMERA->GetY() + WINSIZEY - 25, status, strlen(status));	
}
