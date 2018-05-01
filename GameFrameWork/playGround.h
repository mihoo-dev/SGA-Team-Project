#pragma once
#include "gameNode.h"
#include "StartScene.h"
#include "TutorialScene.h"
#include "GraveyardScene.h"
#include "WorldScene.h"
#include "EndScene.h"
#include "LoadingScene.h"
#include "StoreScene.h"

class playGround : public gameNode
{
private:
    gameNode * _startScene;
    gameNode * _tutorialScene;
	gameNode * _graveyardScene;
	gameNode * _worldScene;
    gameNode * _endScene;
    gameNode * _loadingScene;
	gameNode * _storeScene;

    int _alpha;

    bool _sceneChange1;
    bool _sceneChange2;
	bool _sceneChange3;
	bool _sceneChange4;
	bool _sceneChange5;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();



	playGround();
	~playGround();
};

