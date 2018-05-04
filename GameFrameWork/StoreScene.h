#pragma once
#include "gameNode.h"
#include "StarPoint.h"
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
	RECT _rc;
	image* _speechBalloon;
	image* _priceTagImage;
	image* _backBtnImage;

	BalloonState _state;

	Item* _starPoint;

	bool _isSpeech;

	int _starCost;
	int _speechCnt;
	int _coins;
    int _stars;
	int _alpha;

	vector<string> _vItem;
public:
	StoreScene();
	~StoreScene();

	HRESULT init();
	void update();
	void release();
	void render();

	void checkCost(int i);

	void initBackBtn();
	void updateBackBtn();
	void renderBackBtn();
};

