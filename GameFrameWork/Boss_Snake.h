#pragma once
#include "gameNode.h"

class Boss_Snake : public gameNode
{
private:
	image*					_img;
	animation*				_motion;
	float					_x, _y;
	BOSS_SNAKE				_state;
	BOSS_SNAKE_DIRECTION	_direction;
	RECT					_rc;
	RECT					_body, _head;
	int						_count;
	BOOL					_isPlay;
	int						_startX, _endX;

public:
	Boss_Snake();
	~Boss_Snake();

	HRESULT init();
	void release();
	void update();
	void render();

	void Set(float x, float y);
	void Operation();
	void Move(string direction);
};

