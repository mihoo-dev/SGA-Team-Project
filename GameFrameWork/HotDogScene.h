#pragma once
#include "gameNode.h"

class PlayerManager;

class HotDogScene :	public gameNode
{
private:
	PlayerManager*	_pm;
	
	float				_loopX;
public:
	HotDogScene();
	~HotDogScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

