#pragma once
#include <vector>

#define SIZEOFTRACE			22
#define BRIDGEX				2010
#define BRIDGETOPSTART		1484
#define BRIDGETOPEND		1630
#define BRIDGEBOTTOMSTART	1600
#define BRIDGEBOTTOMEND		1450

//클래스 전방선언
class World_Bridge;

struct tagTrace
{
	int						x, y;
	WORLD_CHARACTER_STATE	state;
	animation*				motion;
	int						idleFrame;
};

class World_Character
{
private:
	float						_x, _y;								//중점 좌표
	float						_angle;								//각도
	image*						_img;								//이미지
	animation*					_motion;							//움직임 애니메이션
	WORLD_CHARACTER_STATE		_state;								//상태
	int							_frameX, _frameY;					//프레임 번호(X,Y)
	int							_probeLeft, _probeRight;			//픽셀 검출 기준 좌우 좌표
	int							_probeUp, _probeDown;				//픽셀 검출 기준 상하 좌표 
	int							_collisionRight, _collisionLeft;	//좌우 충돌 체크
	int							_collisionUp, _collisionDown;		//상하 충돌 체크
	RECT						_rc;								//렉트
	BOOL						_right, _left, _up, _down;			//키입력 상태


private:
	tagTrace					_traceFinn;							//핀 이동경로를 위한 구조체
	vector<tagTrace>			_vTrace;							//핀 이동경로를 담을 벡터
	image*						_jakeImg;							//제이크 이미지
	float						_jakeX, _jakeY;						//제이크 좌표
	animation*					_jakeMotion;						//제이크 모션
	BOOL						_followTrace;						//추적 할지 말지 확인
	int							_traceIndex;						//벡터 인덱스

private:
	World_Bridge*				_bridge;							//다리 클래스
	BOOL						_canMakeBridge;						//다리 생성 가능한 지역에 위치 하고 있는지 확인
	BOOL						_meetDog;							//강아지 NPC 만났는지 확인
	WORLD_MAKE_BRIDGE			_bridgeState;						//다리 생성 상태

private:
	BOOL						_pressX;
	int							_Xframe;
	int							_Xcount;
	BUTTON_STATE				_buttonState;
	COLORREF					_colorStore;
	COLORREF					_colorBridge;
	COLORREF					_colorGraveyard;

public:
	World_Character();
	~World_Character();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	//FINN 관련 함수
	void CheckDirection();
	void CheckPixel();
	void ChangeState();
	void SetCamera();
	void Move();
	
	//JAKE 관련 함수
	void CheckTrace();
	void SaveTrace(int index);
	void DrawJake(HDC hdc);

	//다리 생성 관련 함수
	void MakeBridge();
	void BridgeOperation();
	WORLD_MAKE_BRIDGE GetBridgeState() { return _bridgeState; }
	void SetBridgeState(WORLD_MAKE_BRIDGE state) { _bridgeState = state; }

	//버튼 함수
	void button();

	float GetX() { return _x; }
	float GetY() { return _y; }
	
	void SetFinnState(WORLD_CHARACTER_STATE state) { _state = state; }

	void CheckStatus(HDC hdc);

	void GetAdressBridge(World_Bridge* bridge) { _bridge = bridge; }
};

