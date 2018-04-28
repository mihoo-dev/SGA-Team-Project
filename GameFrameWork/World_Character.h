#pragma once

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


public:
	World_Character();
	~World_Character();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setImage(string imageKey);
	virtual void checkDirection();
	virtual void checkPixel();
	virtual void changeState();
	virtual void setCamera();
	virtual void move();

	float getX() { return _x; }
	float getY() { return _y; }
};

