#pragma once
#include "gameNode.h"

class Store;

enum BalloonState
{
	WELCOME,
	THANKS,
	DISCARCE,
};

class StoreScene : public gameNode
{
private:
	Store* _store;
	image* _speechBalloon;
	BalloonState _state;

	bool _isSpeech;

	int _starCost;
	int _speechCnt;

public:
	StoreScene();
	~StoreScene();

	HRESULT init();
	void update();
	void release();
	void render();
};

