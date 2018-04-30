#pragma once

class World_Character;

class World_Bridge
{
private:
	World_Character*	_finn;

private:
	int		_x, _y;					//다리 만들 좌표
	int		_state;					//다리 상태 0:다리 없음, 1:생성 가능, 2:생성중, 3:생성 완료, 4:철수중
	image*	_img;					//다리 이미지
	int		_frameX, _frameY;		//프레임XY
	int		_count;					//카운트
	BOOL	_startAni;				//애니메이션 스타트
	int		_bridgeDirection;		// 0 : 북에서 남으로, 1 : 남에서 북으로


public:
	World_Bridge();
	~World_Bridge();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void MakeBridge();
	void RemoveBridge();

	int GetBridgeDirection() { return _bridgeDirection; }
	void SetFrameX(int x) { _frameX = x; }
	void SetFrameY(int y) { _frameY = y; }
	void SetBridgeDirection(int direction) { _bridgeDirection = direction; }

	void SetStartAni(BOOL start) { _startAni = start; }

	void GetAdressFinn(World_Character* finn) { _finn = finn; }
};

