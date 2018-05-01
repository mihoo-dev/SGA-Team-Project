#pragma once
#include "gameNode.h"
class StoreNPC : public gameNode 
{
private:
	image* _NPCImage;

	float _x, _y;

	int _frameX, _frameY;
	int _frameUpdateTime;
	int _currentTime;
public:
	StoreNPC();
	~StoreNPC();

	HRESULT init(float x, float y);
	void update();
	void release();
	void render();
};

