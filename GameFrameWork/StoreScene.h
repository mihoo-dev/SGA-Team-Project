#pragma once
#include "gameNode.h"
#include <vector>

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

	vector<string> _vItem;
public:
	StoreScene();
	~StoreScene();

	HRESULT init();
	void update();
	void release();
	void render();
};

