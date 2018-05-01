#pragma once
#include "gameNode.h"

class Store;

class StoreScene : public gameNode
{
private:
	Store* _store;

public:
	StoreScene();
	~StoreScene();

	HRESULT init();
	void update();
	void release();
	void render();
};

